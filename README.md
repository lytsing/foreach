This is a command for shell.

* How to use ? *

1.**Simplest**

```
$ foreach -n 5 "echo hello"

```
if use ruby to write, it will like this:

```
irb(main):001:0> 5.times {puts "hello"}
hello
hello
hello
hello
hello
=> 5
irb(main):002:0>
```

2.**Support Parmeter**

```
$cat iplist
210.34.0.222 bbs.xmu.edu.cn

$ cat iplist | foreach -w 20 "sshscp.pl -p 1949 -r #1 -c 'md5sum '"
```

 #1, #2, ... respectively is the first parameter, the second ...

If the iplist file has more one line, it also can work!

Reporting Bugs
==============

Bug reports for foreach should be send to:

    hlqing@gmail.com

Enjoy!

Lytsing Huang

