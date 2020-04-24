# 第二章 常用Linux命令

### 1、系统工作命令
#### man
> man可以查看某一命令的说名手册
```
man 命令
man即使manua--手册的缩写
```

#### echo
> echo 命令用于在终端输出字符串或变量提取后的值，格式为“echo [字符串 | $变量]”
```
echo hello
echo $PATH  ---环境变量
```

#### date
> date 命令用于显示及设置系统的时间或日期，格式为“date [选项] [+指定的格式]

```
date
date "+%Y-%m-%d %H:%M:%S"  按格式查看
date -s "20170901 8:30:00" 设置时间
date "+%j"   查看今天时今年的第几天
```

#### reboot
> reboot 命令用于重启系统，其格式reboot
```
reboot 
```

#### poweroff
> poweroff 命令用于关闭系统，其格式poweroff
```
poweroff 
```

####wget
> wget 命令用于在终端中下载网络文件，格式为“wget [参数] 下载地址”
```
wget [url]  去url下载...
wget -r -p [url]  递归，全部的下载
```

#### ps
> ps 命令用于查看系统中的进程状态，格式为“ps [参数]”

```
ps -aux  三参数合写  ps常与管道合用
```

#### top
> top 命令用于动态地监视进程活动与系统负载等信息，其格式为 top  类似于任务管理器
```
top
```

#### kill
> kill 命令用于终止某个指定 PID 的服务进程，格式为“kill [参数] [进程 PID]”。 
```
kill 2156  进程id
```

#### killall
> killall 命令用于终止某个指定名称的服务所对应的全部进程，格式为：“killall [参数] [进 程名称]”。 
```
killall httpd
```

### 2、系统状态检测命令 

#### uname
> uname 命令用于查看系统内核与系统版本等信息，格式为“uname [-a]”。 
```
uname -a 
```

#### free
> free 用于显示当前系统中内存的使用量信息，格式为“free [-h]”。 
```
free -h 
```

#### who
> who 用于查看当前登入主机的用户终端信息，格式为“who [参数]”。 
```
who
```

#### last
> last 命令用于查看所有系统的登录记录，格式为“last [参数]”
```
last
```

**history**
> history 命令用于显示历史执行过的命令，格式为“history [-c]”。 
```
history
history -c  c是clear
```

### 3、工作目录切换命令 

**pwd**
> pwd 命令用于显示用户当前所处的工作目录，格式为“pwd [选项]”。 
```
pwd
```

**cd**
> cd 命令用于切换工作路径，格式为“cd [目录名称]”。 
```
cd /etc
cd /bin/sda
cd ~  进入家目录
```

**ls**
> ls 命令用于显示目录中的文件信息，格式为“ls [选项] [文件] ”。 
```
ls -al          all+list
ls -ld /ect     d是查看目录信息
```

### 4、文本文件编辑命令 

**cat**
> cat 命令用于查看纯文本文件（内容较少的），格式为“cat [选项] [文件]”。 
```
cat -n a.txt        -n指列出行号
```

**more**
> more 命令用于查看纯文本文件（内容较多的），格式为“more [选项]文件”。 
```
more initial-setup-ks.cfg
```

**head**
> head 命令用于查看纯文本文档的前 N 行，格式为“head [选项] [文件]”。 
```
head -n 20 initial-setup-ks.cfg  20行
```

**tail**
> tail 命令用于查看纯文本文档的后 N 行或持续刷新内容，格式为“tail [选项] [文件]”。 
```
tail -f /var/log/messages 
tail 命令强悍的功能是可以持续刷新一个文件的内容，当想要实时 查看新日志文件时，这特别有用，此时的命令格式为“tail -f 文件名
```

**tr**
> tr 命令用于替换文本文件中的字符，格式为“tr [原始字符] [目标字符]”。 
```
cat anaconda-ks.cfg | tr [a-z] [A-Z]
与重定向一起使用
```

**wc**
> wc 命令用于统计指定文本的行数、字数、字节数，格式为“wc [参数] 文本”。 
```
wc -l /etc/passwd       -l=line=只显示行
```

**stat**
> stat 命令用于查看文件的具体存储信息和时间等信息，格式为“stat 文件名称''
```
stat anaconda-ks.cfg 
```

**cut**
> cut 命令用于按“列”提取文本字符，格式为“cut [参数] 文本”。 
```
cut -d: -f1 /etc/passwd 
用-f 参数来设置需要看的列数，用-d 参数来设置间隔符号
```

**diff**
> diff 命令用于比较多个文本文件的差异，格式为“diff [参数] 文件”。 还可以使用-c 参数来详细比较出多个文件的差异之处，这绝对是判断文件是否被篡改的有力神器
```
diff --brief diff_A.txt diff_B.txt   只看是否相同
diff -c diff_A.txt diff_B.txt  详细比较
```

### 5、文件目录管理命令 

**touch**
> touch 命令用于创建空白文件或设置文件的时间，格式为“touch [选项] [文件]”。 
```
touch -d "2017-05-04 15:44" anaconda-ks.cfg 
```

**mkdir**
> mkdir 命令用于创建空白的目录，格式为“mkdir [选项] 目录”。 
```
mkdir ff
mkdir -p a/b/c/d/e      按层级关系创建  
```

**cp**
> cp 命令用于复制文件或目录，格式为“cp [选项] 源文件 目标文件”。 
```
cp install.log x.log 
```

**mv**
> mv 命令用于剪切文件或将文件重命名，格式为“mv [选项] 源文件 [目标路径|目标文件名]” 。
```
mv x.log linux.log 
如果 在同一个目录中对一个文件进行剪切操作，其实也就是对其进行重命名： 
```

**rm**
> rm 命令用于删除文件或目录，格式为“rm [选项] 文件”。 
```
rm -f linux.log   不询问删除
rm -r -f lili     递归删除目录·
```

**dd**
> dd 命令用于按照指定大小和个数的数据块来复制文件或转换文件，格式为“dd [参数]” 。 
```
dd if=/dev/zero of=560_file count=1 bs=560M
用 dd 命令从/dev/zero 设备文件中取出一个大小为 560MB 的数据块，然后 保存成名为 560_file 的文件 
```

**file**
> file 命令用于查看文件的类型，格式为“file 文件名”。
```
file anaconda-ks.cfg 
file /dev/sda 
```

### 6、打包压缩与搜索命令

**tar**
> tar 命令用于对文件进行打包压缩或解压，格式为“tar [选项] [文件]”
```
tar -czvf etc.tar.gz /etc 
一般使用“tar -czvf 压缩包名 称.tar.gz 要打包的目录”命令把指定的文件进行打包压缩；
```

**grep**
> grep 命令用于在文本中执行关键词搜索，两 个常用的参数：-n 参数用来显示搜索到信息的行号；-v 参数用于反选信息并显示匹配的结果，格式为 “grep [选项] [文件]” 
```
grep /sbin/nologin /etc/passwd 
```

**find**
> find 命令用于按照指定条件来查找文件，格式为“find [查找路径] 寻找条件 操作”。 
```
find /etc -name "host*" -print 
获取到etc中所有以 host 开头的文件列表

find / -perm -4000 -print 
如果要在整个系统中搜索权限中包括 SUID 权限的所有文件（详见第 5 章），只需使用 -4000 即可
```

### 一个实验：
*在整个文件系统中找出所有归属于 linuxprobe 用户的文件并复制到 /root/findresults目录*

```
find / -user linuxprobe -exec cp -a {} /root/findresults/ \; 
```

*该实验的重点是“-exec {}   \;”参数，其中的{}表示 find 命令搜索出的每一个文 件，并且命令的结尾必须是“\;”。*




-------------------------------------
> 感谢刘遄老师提供的开源优秀教材《Linux就该这么学》www.linuxprobe.com 