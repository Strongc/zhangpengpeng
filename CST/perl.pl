运行perl
  perl file.pl
Perl语言中的许多内置函数也是有效关键字，调用时可以不加括号。

Perl  - Practical Extraction and Report Language
帮助文档 perldoc
       perldoc perl/perlsyn/perlop/perlre/....
       内置函数 perldoc -f functionName
       模块      perldoc 模块名   (模块名.pm)
     ToHtml:   perldoc -u subject | pod2html > a.html

调试  perl -d a.pl
   l 列出源代码；b 设置断点； s 单步； n 单过程； x 打印变量；
   h 帮助； r 从当前返回； c 继续； q 退出。

 1 use strict;
 2 use warnings;
 3 
 4 while (<DATA>)
 5 {
 6         if (/^#/) {
 7                 next;
 8         }
 9         my @grades = split /[ \t]+/, $_;
10         my $name = shift @grades;
11         my $ave = ($grades[0] + $grades[1] + $grades[2]) / 3;
12         print "Student $name Average $ave\n";
13 }
14 
15 __DATA__
16 # Student       Grade   Grade   Grade
17 oualline        98      95      92
18 smith           75      84      99
19 jones           45      26      55

perl 只有一种数据类型：字符串。   #Perl以#开始注释。
局部变量 my  :  my $size = 42;  => my $size = "42";
标量$；数组@；散列%。
双引号""，Perl会解释变量和转义，而单引号''则不会。
     如何输出 42inches    "$name\t${size}inches";

Perl 比C多出的几个运算符：
    . 字符串串联； ** 幂； x 3 重复3次。

读取输入 $var = <STDIN>;  读取整行，包括换行。
     chomp($var); 剪掉字符串结尾的新行。

if/else, while, for 均与C类似。
   if, elsif, else   die("打印出错并退出");
条件运算符：   数  字   ==    !=    <   <=   >   >=
                    字符串  eq     ne    lt    le     gt  ge
  defined 函数测试是否有值/undef
   perl 中的真假：  undef, 0, "" 均为false，其余为true。

 1 use strict;
 2 use warnings;
 3 
 4 open IN_FILE, "<ave.pl" or die("can't open in_file");
 5 open OUT_FILE, ">c.pl" or die("can't open out_file");
 6 while (1) {
 7         my $var = <IN_FILE>;
 8         if (not defined($var)) {
 9                 last;
10         }
11         print OUT_FILE $var;
12 }
13 close(IN_FILE);
14 close(OUT_FILE);

my @list = ("Sam", "Joe", "Fred", "Sue");
   $list[0], $list[1],...   $#list 最后元素索引，即元素个数减一。
my @array = (1, "hi", $data, @list);
  my @array = qw(Tom Dick Harry); #空格隔开而非逗号
push(@array, $var);  $element = pop(@array);
unshift, shift与push, pop类似，但在数组起始处。
@array[1,0] = @array[0,1]; @array[0, $#array]=(-1,-1); @array[0..9]=((0)x10);
splice函数可以删除或替换数组的一部分。
split函数分解字符串为数组，@array = split /PAT/, EXPR;
join 合成字符串， my $line = join("\t", @data, $a);
sort 排序数组， my @sort = sort @array;

正则表达式放在两斜杠(//)之中。
运算符 =~ 用于检查左边的字符串是否与右边的正则表达式匹配。
替换 $line =~ s/<old>/<new>/<flag>;   flag为g,i；
grep通过一个字符串列表搜索返回一个与正则表达式匹配的字符串数组：my @todoLine = grep /TODO:/, @file_lines;

foreach $element (@array) { }
隐式变量 $_
           if (/^#/)    => if ($_ =~ /^#/)
           <STDIN>  => $_ = <STDIN>
next 跳至下一个循环； redo 重做这个循环。
翻译 $hex =~ tr/abcdef/ABCDEF/;
= 左边可为数组  ($first, $second) = ($second, $first);
散列 %,  my %flags;     delete($flags{end});
             $flags{start} = ".....";
             $flags{middle} = ".....";
             $flags{end} = "......";
Perl 中引用类似于C指针，用\获得引用， 引用就像个名字，具体用时还要在前面加上 $ @ %等。
     my $ref = \$var 或 \@array 或 \%hash
   $$ref; @$ref, $$ref[0], $#$ref; $ref->{key}, $$ref{key};
方括号[]创建一个新数组，并返回其引用；还可创建一个数组拷贝，返回其引用。
     my $ref = ["red", "white", "blue"];
     my $copy_ref = [@array];

子程序 subroutine
    sub fun(arg_list) {funBody;}
调用时，参数传给数组@_，可直接用@_，也可用shift逐个移出。
参数定义，用$,@,%,\@等表示，有几个参数就用几个记号，，参数列表为空时，表示参数类型任意、数量任意。
 1 use strict;
 2 use warnings;
 3 
 4 sub timediff($$)
 5 {
 6         my $starttime = shift;
 7         my $endtime = shift;
 8 
 9         my $result = $endtime - $starttime;
10 
11         return ($result);
12 }
13 
14 my $elapsed = timediff(1,5);
15 
16 print $elapsed;

包package类似于C++中的类，必要时要用到作用域运算符(::)。
 1 use strict;
 2 use warnings;
 3 
 4 my $calling = 0;
 5 
 6 package call;
 7 
 8 my $in_call = 0;
 9 sub start()
10 {
11         $in_call = 1;
12         return $in_call;
13 }
14 
15 package main;
16 
17 $calling++;
18 $calling += call::start();
19 
20 print $calling;

here-doc语法为   <<关键字， 直到发现该关键字时结束。
