# 代码规范和约定
# 命名规则
## 变量/方法
### 普通变量和普通函数
**变量/函数**名称遵从**驼峰命名**规则。如果单词过长，会取开头的3到4个字符进行缩减。
```cpp
int sampleVariable;

void sampleFunction();

double shortVar;

void shortFunc();
```
### 特殊修饰符
`const`修饰的**变量**会被写为全大写，在单词分词时使用下划线
```cpp
const int CONST_INT;
```

`static`修饰的**变量/公用函数**会变成与类命名方式相似的命名
```cpp
static int IntVariable;

static void StaticFunction();
```

`static`修饰的**私用函数**仍然保持驼峰命名法。

`unsigned`修饰的变量会在变量前增加`u`
```cpp
unsigned int uintVariable;
```
当多个修饰符都存在时，按照声明的顺序书写前缀。如果有一个修饰是`const`，则在前缀后添加`_`
```cpp
static const unsigned int SU_INT_VARIABLE;
```

## using
当使用`using`语句重写标准库类型时，将会维持标准库命名规则，使用小写字母命名类型别名。
```cpp
using indexes = std::vector<int>;
using shared_mutex = std::shared_mutex;
```

---
## 类名称
>- 类名称将被写为由开头首字母大写单词组成的名称。
>- 如果是`Factory`类则会以`Factory`结尾
>- 如果是`Singleton`类则会继承`Singleton`类，并在类中使用`INVITE_SINGLETON`宏。在PrimedDB中，所有的`Manager`类都是`Singleton`类。
>- 如果是相关的静态函数，都将会被写在以`Functions`结尾的`static`类中作为`public`方法

---
## 命名限制
>- 变量以及方法的命名总是概括其主要功能。
>- 成员变量总是以m_开始，除非当前成员变量为const或static类型且有特殊用途
>- 单字符变量全部为计数器变量。
>- 以`uptr`结尾的变量总是`unique_ptr`
>- 以`sptr`结尾的变量总是`shared_ptr`
>- 以`ptr`结尾的变量总是裸指针，且其总是由一个工厂创建的，并且需要由这个工厂类提供的析构方法销毁，且需要保证在销毁后不对其进行操作，应当在调用工厂析构方法时将指针设为nullptr。
>- `get/set`开头的方法用于对字段进行获取或修改。当`get`返回对象时，大部分时候返回的是原对象的引用。
>- `take`开头的方法用于返回对象的`uptr/sptr`
>- `is`开头的方法总是返回`bool`或基于`-1,0,1`的比较
>- `func`结尾的变量总是表明这是一个lambda对象或是一个`function<>`对象
>- `format()`方法总是表明是对当前类可打印部分进行打印。拥有`string format() const/string& format() const`的类可以直接使用Log类型进行打印

# 文档规范和约定
## 类，函数，变量名称
- 以上名称都会以`名称`方式呈现。但接口介绍时会使用 **名称** 来表示一个函数，以区别于返回值类型和模板声明。
- 当书写函数时，将会使用`:`在函数后面表示函数返回值类型。
	- 当一个函数在代码中为`auto`类型时，文档会直接描述实际类型，而不是只使用auto。
	- 当函数返回值类型为`void`时，`void`将会被省略
	- 成员变量的`const`修饰将会被写在参数列表之后并加粗
- 当函数为模板函数时，模板要求将会写在函数名称前并使用空格隔断。
- 文档中类名称后的为类的类型，如泛型（generic）以及单例类（Singleton）等
