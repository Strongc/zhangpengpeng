����perl
  perl file.pl
Perl�����е�������ú���Ҳ����Ч�ؼ��֣�����ʱ���Բ������š�

Perl  - Practical Extraction and Report Language
�����ĵ� perldoc
       perldoc perl/perlsyn/perlop/perlre/....
       ���ú��� perldoc -f functionName
       ģ��      perldoc ģ����   (ģ����.pm)
     ToHtml:   perldoc -u subject | pod2html > a.html

����  perl -d a.pl
   l �г�Դ���룻b ���öϵ㣻 s ������ n �����̣� x ��ӡ������
   h ������ r �ӵ�ǰ���أ� c ������ q �˳���

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

perl ֻ��һ���������ͣ��ַ�����   #Perl��#��ʼע�͡�
�ֲ����� my  :  my $size = 42;  => my $size = "42";
����$������@��ɢ��%��
˫����""��Perl����ͱ�����ת�壬��������''�򲻻ᡣ
     ������ 42inches    "$name\t${size}inches";

Perl ��C����ļ����������
    . �ַ��������� ** �ݣ� x 3 �ظ�3�Ρ�

��ȡ���� $var = <STDIN>;  ��ȡ���У��������С�
     chomp($var); �����ַ�����β�����С�

if/else, while, for ����C���ơ�
   if, elsif, else   die("��ӡ�����˳�");
�����������   ��  ��   ==    !=    <   <=   >   >=
                    �ַ���  eq     ne    lt    le     gt  ge
  defined ���������Ƿ���ֵ/undef
   perl �е���٣�  undef, 0, "" ��Ϊfalse������Ϊtrue��

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
   $list[0], $list[1],...   $#list ���Ԫ����������Ԫ�ظ�����һ��
my @array = (1, "hi", $data, @list);
  my @array = qw(Tom Dick Harry); #�ո�������Ƕ���
push(@array, $var);  $element = pop(@array);
unshift, shift��push, pop���ƣ�����������ʼ����
@array[1,0] = @array[0,1]; @array[0, $#array]=(-1,-1); @array[0..9]=((0)x10);
splice��������ɾ�����滻�����һ���֡�
split�����ֽ��ַ���Ϊ���飬@array = split /PAT/, EXPR;
join �ϳ��ַ����� my $line = join("\t", @data, $a);
sort �������飬 my @sort = sort @array;

������ʽ������б��(//)֮�С�
����� =~ ���ڼ����ߵ��ַ����Ƿ����ұߵ�������ʽƥ�䡣
�滻 $line =~ s/<old>/<new>/<flag>;   flagΪg,i��
grepͨ��һ���ַ����б���������һ����������ʽƥ����ַ������飺my @todoLine = grep /TODO:/, @file_lines;

foreach $element (@array) { }
��ʽ���� $_
           if (/^#/)    => if ($_ =~ /^#/)
           <STDIN>  => $_ = <STDIN>
next ������һ��ѭ���� redo �������ѭ����
���� $hex =~ tr/abcdef/ABCDEF/;
= ��߿�Ϊ����  ($first, $second) = ($second, $first);
ɢ�� %,  my %flags;     delete($flags{end});
             $flags{start} = ".....";
             $flags{middle} = ".....";
             $flags{end} = "......";
Perl ������������Cָ�룬��\������ã� ���þ�������֣�������ʱ��Ҫ��ǰ����� $ @ %�ȡ�
     my $ref = \$var �� \@array �� \%hash
   $$ref; @$ref, $$ref[0], $#$ref; $ref->{key}, $$ref{key};
������[]����һ�������飬�����������ã����ɴ���һ�����鿽�������������á�
     my $ref = ["red", "white", "blue"];
     my $copy_ref = [@array];

�ӳ��� subroutine
    sub fun(arg_list) {funBody;}
����ʱ��������������@_����ֱ����@_��Ҳ����shift����Ƴ���
�������壬��$,@,%,\@�ȱ�ʾ���м����������ü����Ǻţ��������б�Ϊ��ʱ����ʾ�����������⡢�������⡣
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

��package������C++�е��࣬��ҪʱҪ�õ������������(::)��
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

here-doc�﷨Ϊ   <<�ؼ��֣� ֱ�����ָùؼ���ʱ������
