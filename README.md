ctpl-engine
===========

##ctpl-engine是什么
为了解决在某些极端情况下，无法使用流行的模板引擎(例如某些情景下无法使用php环境)，用来做html视图分开的一种模板引擎替代，直接使用c语言编写


##ctpl-engine有哪些特点

* c语言标准库编写，cgi中直接调用
* 在某些嵌入式系统上，可以快速的实现视图业务分离
* 渲染速度比普通引擎快

##目前状态
* 2013-11-01 实现了字串标签的替换
* 2013-11-04 实现了嵌套key.key.key[.keys]的调用方式
* 2013-11-08 修复了assign a.b 字符串后 使用 {$a.b.c}会导致seg fault的问题
* 2013-11-08 引入变量类型控制机制（暂时支持TYPE_STRING|TYPE_HASH）

##Todo
* 支持复杂类型的key.key嵌套调用[已完成]
* 嵌套标签的宏支持，简化调用过程:直接使用ASSIGN("key1.key2", "val")完成嵌套[已完成]
* 条件语句 if else endif支持

##使用方法

	[调用]
	#include <tpl.h > //引入文件支持
	g_var = hash_new(); //初始化全局变量表
	ASSIGN("a", "三金个小王八蛋"); //字符串变量指定
	ARRAY_INIT(b); //初始化数组
	ARRAY_INSERT(b, "c", "确实啊"); //数组内变量赋值
	ARRAY_INSERT(b, "d", "而且还是ED");
	ARRAY_INIT(e);
	ARRAY_INSERT(e, "C", "小儿hoho~");
	ARRAY_APPEND(e, b); //创建数组的子数组
	ARRAY_DONE(b); //将数组挂到全局变量	
	render("a.tpl"); //执行渲染

	[模板a.tpl]
	key a : {$a}
	key b.c : {$b.c}
	key b.c.d : {$b.c.d}
	key b.d : {$b.d}
	key b.e.C : {$b.e.C}

	[输出]
	key a : 三金个小王八蛋
	key b.c : 确实啊
	key b.c.d : 
	key b.d : 而且还是ED
	key b.e.C : 小儿hoho~

##关于作者

* 邮件(hellovigoss#gmail.com, 把#换成@)
* weibo: [@v5871b崽](http://weibo.com/hellovigoss)
