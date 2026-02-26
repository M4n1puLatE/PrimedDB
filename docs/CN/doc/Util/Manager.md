# Manager
> PrimedDB中用于创建会以独立线程形式长期驻留并提供系统服务（如错误处理，日志信息打印输出等）的管理者类型的基类。

所属命名空间： `Util`

Manager的子类只需要对自己的成员保证线程安全。并最好在使用容器的情况下在注册的服务中加锁。

# 类型原理
1. 在`Manager`类型中有一个`static`的管理线程。该线程由多个管理者服务共用，线程通过待执行任务队列在不同子类提交的任务间进行上下文切换。这种设计是为了确保线程的利用率最大化，不会存在部分管理类型没有任务执行但还需要占用一个线程，且在唤醒和沉睡时浪费CPU。
2. `Manager`中会使用变长数组存储子类注册到基类的服务
3. 在子类提交任务并唤醒管理线程后，管理线程会执行所有子类提交的任务，直到待执行任务队列为空。
4. 待执行队列为子类注册新服务时获取的id，也即注册服务时变长数组`end`位置的下标。
5. **服务**只能注册，**不能被撤销**，因为这些服务应当被设计为持续服务系统组件直到系统关闭的。
![](pic/Pasted%20image%2020260225213811.png)


# 使用方法
继承`Manager`方法并在子类中实现`service`（`Manager`线程中运行的管理服务）和`condition`（线程启动条件）并传入构造函数进行构造（使用`bind`或`lambda`表达式）

# 类和接口声明
```cpp
class Manager
{
	using service = std::function<void()>;
	using awake_condition = std::function<bool()>;

	static std::thread sm_service;
	static mutex sm_conditionMutex;
	static std::condition_variable sm_threadNotifier;
	static std::atomic_bool sm_terminate;
	static std::atomic_bool sm_conditionFlag;


	static std::vector<service> sm_serviceArray;
	static std::deque<size_t> sm_executeQueue;
	static shared_mutex sm_containerMutex;

private:
	static void manageService();


	awake_condition m_condition;
	const size_t m_id;
	static size_t taskSize();
	static size_t serviceSize();
	static void add(service&& service);
	static void newTask(size_t id);
	static bool isEmpty();
	static bool isServiceEmpty();
	static void urgentTask(size_t id);
protected:
	Manager(std::function<void()>&& customService, std::function<bool()>&& condition);
	void notify() const;
	void submit() const;
	void notifyNow() const;
	 
public:
	static bool isTerminate();

	static void join();
	static void terminate();
	static void notifyTerminate();
	~Manager() = default;
};
```

# 成员变量与类型别名
### 类型别名
- **service**：用于描述管理线程运行的服务，为`void`型的函数
	- `std::function<void()>`
- **awake_condition**：唤醒条件，用于在条件满足时唤醒线程
	- `std::function<bool()>`

### 成员变量
#### 静态成员变量
1. **sm_service**: `std::thread` 
	- 管理者服务线程，执行子类提交的任务。
2. **sm_conditionMutex**: `std::mutex`
	- 管理者线程的条件变量的等待锁
3. **sm_threadNotifier**: `std::condition_variable `
	- 管理者线程的条件变量，用于等待指定条件和唤醒管理者线程
4. **sm_terminate**: `std::atomic_bool`
	- 管理者线程截止状态
5. **sm_conditionFlag**: `std::atomic_bool`
	- 管理线程激活条件。
	- 如果当前任务队列存在未执行任务且服务数组中存在指定服务时会运行管理线程
	- 在当前提交的所有任务全部结束后重设为`false`
6. **sm_serviceArray**: `std::vector<service>`
	- 存储所有子类注册服务的数组
7. **sm_executeQueue**: `std::deque<size_t>`
	- 存储待执行任务的队列
	- 如果任务属于`urgent`任务，则会从队列前部插入。
8. **sm_containerMutex**: `shared_mutex`
	- 容器锁，用于同步上面两个容器的操作。

---
#### 普通成员变量
1. m_condition: `awake_condition` 
	- 管理线程唤醒条件函数，由子类注册
	- 在唤醒管理线程前会执行函数检测是否满足条件。
2. `const` m_id:  `size_t`
	- 当前`Manager`子类的`Manager`id。


# 接口
## static方法
### private
1. **manageService()**
	- `Manager`管理线程运行的管理服务
2. **taskSize()**: `size_t`
	- 返回当前有多少个未执行任务
3. **serviceSize()**: `size_t`
	- 返回当前有多少个已注册服务
4. **add(service&& service)**
	- 注册一个新的服务到服务数组中
5. **newTask(size_t id)**
	- 创建一个新的待执行任务
6. **isEmpty()**: `bool`
	- 检测当前待执行队列是否为空
7. **isServiceEmpty()**: `bool`
	- 检测当前已注册服务数组是否为空
8. **urgentTask(size_t id)**
	- 创建一个新的优先待执行任务，并优先执行
### public
1. **isTerminate()**: `bool`
	- 检测管理线程是否关闭
2. **join()**
	- 等待管理线程结束
3. **terminate()**
	- 通知管理线程关闭，并等待其结束
4. **notifyTerminate()**
	- 通知管理线程关闭

## 普通接口
### protected
1. **notify() const**
	- 唤醒管理线程，并提交新的待执行任务
	- 如果当前管理线程正在运行，则不会执行唤醒，只会提交新的待执行任务
2. **submit() const**;
	- 提交新的待执行任务
3. **notifyNow() const**;
	- 唤醒管理线程，并提交新的优先待执行任务
	- 如果当前管理线程正在运行，则不会执行唤醒，只会提交新的优先待执行任务