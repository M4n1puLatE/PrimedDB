# Util (Static)
> 给出部分静态通用函数，如按照规则split长字符串。

所属命名空间：`Util`

# 使用方法
直接使用`Util`类名称调用静态函数，所有工具通用函数都是`public`的。

# 类型别名
```cpp
using indexes = std::vector<size_t>;
using string = std::string;
using substring = std::vector<string>;
```
- `indexes`：容器内满足条件的元素下标位置数组
- `string`：在类内简化标准库string名称
- `substring`：某个字符串按照规则split的子字符串数组

# 类声明与接口说明
```cpp
	class Util
	{

	public:
		// 参数说明
        // str:待分割的字符串
        // delim:分隔符
		// 返回值说明
        // 返回一个索引列表（indexes），索引列表中的元素表示分隔符的位置
		static indexes IndexSplitString(const string& str, char delim);
		// 参数说明
        // str:待分割的字符串
        // delim:分隔符
        // 返回值说明
		// 返回一个子串列表（substring），子串列表中的元素表示分隔后的子串
		static substring SplitString(const string& str, char delim);
		// 参数说明
// result:返回值列表，用于返回所有的分隔符位置
// str:待分割的字符串
// delim:分隔符
		static void IndexSplitString(indexes& result, const string& str, char delim);
		// 参数说明
		// result:返回值列表，用于返回所有的子串
// str:待分割的字符串
// delim:分隔符

		static void SplitString(substring& result,const string& str, char delim);
		// 参数说明
		// //////////////////////
		// str:待解释的字符串
		// indexes:分隔符位置列表(需要与str配对)
		// position:子串索引
		static std::string InterpretString(const string& str,const indexes& , size_t);
	};
```
## 公用接口
1. **IndexSplitString(const string& str, char delim)**: `indexes`
	- 将字符串分割成若干子字符串并返回下标数组。
2. **SplitString(const string& str, char delim)**: `substring`
	- 将字符串分割成若干子字符串并返回子字符串数组。
3. **IndexSplitString(indexes& result, const string& str, char delim)**
	- 接口1的高级实现，要求调用者传入结果数组的引用，而不是重新构造新数组。
4. **SplitString(substring& result,const string& str, char delim)**
	- 接口2的高级实现，要求调用者传入结果数组的引用，而不是重新构造新数组。
5. **InterpretString(const string& str,const indexes& , size_t)**: `string`
	- 当返回值为下标数组时，使用这个函数访问指定的子字符串。
	- 该函数要求传入的字符串必须和下标数组代表的字符串一致，否则会抛出标准库异常（访问超限）。