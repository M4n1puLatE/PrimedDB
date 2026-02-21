# TimerPlus (Generic)
> TimerPlus是Timer的子类，增加了暂停和恢复功能，其他Timer拥有的功能详见[Timer文档](Timer.md)。
> 实现原理是增加暂停的$x$时间到开始时间上，以顺延开始时间。

**TimerPlus不是线程安全的**，请在多线程场景下使用`SyncTimerPlus`(未实现)

所属命名空间：`Util`
# 使用方法
- 使用`pause()`暂停当前计时器，并使用`resume()`恢复当前计时器。
- `isPaused()`可以用以查看当前计时器有没有暂停。


# 类声明与接口说明
```cpp
template<class TimeType>
class TimerPlus: Timer<TimeType>
{ 
    TimeType m_pauseBegin;
public:
	void pause();
	bool isPaused() const;
    void resume();
};
```

## 成员变量
1. **m_pauseBegin**: `TimeType`
	- 表明当前暂停的开始时间。

---
## 构造函数
- 默认构造函数
	- 将`m_pauseBegin`设置为0
- 拷贝构造函数
- 移动构造函数

---
## 公用接口
1. **pause()**
	- 暂停当前计时器，将`m_pauseBegin`设置为`Now()`。
2. **isPaused() const**: `bool`
	- 返回当前计时器是否被暂停。
3. **resume()**
	- 恢复当前计时器到非暂停状态。
	- 如果有暂停状态将会修改基类的开始时间。
4. 拷贝运算符
5. 移动运算符
