ctpl-engine
===========

##ctpl-engine是什么
为了解决在某些极端情况下，无法使用流行的模板引擎(例如php)，用来做html视图分开的一种模板引擎替代，直接使用c语言编写


##ctpl-engine有哪些特点

* c语言标准库编写，cgi中直接调用
* 渲染速度比普通引擎快

##目前状态
* 2013-11-01 实现了字串标签的替换


##Todo
*支持复杂类型的key.key嵌套调用

##使用方法
`#include <tpl.h>`    
`ASSIGN(key, value);`   
`render(template_path);`

##关于作者


* 邮件(hellovigoss#gmail.com, 把#换成@)
* weibo: [@v5871b崽](http://weibo.com/hellovigoss)
