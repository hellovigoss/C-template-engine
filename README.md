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

##Todo
*支持复杂类型的key.key嵌套调用[已完成]
*嵌套标签的宏支持，简化调用过程:直接使用ASSIGN("key1.key2", "val")完成嵌套

##使用方法
`#include <tpl.h>`    
`ASSIGN(key, value);`   
`render(template_path);`

##关于作者

* 邮件(hellovigoss#gmail.com, 把#换成@)
* weibo: [@v5871b崽](http://weibo.com/hellovigoss)
