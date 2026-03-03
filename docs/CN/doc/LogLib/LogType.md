# LogType (Enum)

# 枚举类型定义
```cpp
enum class LogType
{
	None,
	Info,
	Debug,
    Warn,
	Error,
	Fatal
};
```
## 枚举值解释
- None: 只包含时间戳的单条信息
- Info: 一般性`Log`信息
- Debug: 表示调试类信息
- Warn: 表示警告类信息
- Error: 表示错误类信息
- Fatal: 表示严重错误类信息
