# Singleton (Generic)
> 单例类型的基类，用于声明一个单例类型。

# 类型原理
通过`Get()`方法构造一个`static`的*Singleton*对象。

# 使用方法
子类通过继承父类并传入子类的类名称，且使用`THIS_IS_SINGLETON`宏将父类设为友元类使得父类可以使用子类的私有构造函数构造`static`的单例对象。

# 类和接口声明
```cpp
template<class T>
class Singleton
{
protected:
	Singleton() = default;

public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	static T& Get();
};
#define	THIS_IS_SINGLETON friend class Singleton
```

## 接口
### 公用接口
- `template<class T>`**Get()**: `T`
	- 构造一个子类的单例对象。
