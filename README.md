汇编模拟器

-   前序遍历序列重新建二叉树（思路）
    -   NNLLL序列，N在二叉树中为父节点，L为叶子节点
    -   可以使用栈进行规约，将序列进栈，当栈中序列为NL或者NLL时，可以归约成L重新进栈，直到栈顶为N

-   链接时出现multiple definition问题
    -   养成在.h文件使用extern进行声明，在.c文件中定义的习惯
    -   头文件使用#ifndef-#define-#endif

-   第一阶段
    -   利用虚拟内存，物理内存，寄存器，指令集去模拟一个ADD程序
    -   使用虚拟地址进行初始化
    -   `uint8_t mm[]`为物理内存，`va2pa()`实现vaddr->paddr的映射

-   栈、树与规约
    -   栈的`push`和`pop`以及树节点的定义可以看作是一个规约的过程
    -   函数的调用也可以理解成是`cpu`和内存进行了一次规约，并且规约到了`%rax`/`%eax`寄存器中

-   `call`、`ret`、`push S`、`pop D`
    -   call调用
        -   rsp-=8，并存入rip++指向的地址，此时rsp指向（存）的是callback后的第一条指令的地址
    -   ret回调
        -   将rsp指向的callback地址赋给rip，再rsp+=8
    -   push S
        -   rsp-=8，再将S存入rsp指向的新空间中
    -   pop D
        -   将rsp指向的内存中的内容存入D中，再rsp+=8

-   表达式求值
    -   op栈可以看作一个单调栈，定义（+-*/）优先级，+- == 0；*/ == 1；优先级1最高
    -   入op栈的时候，根据单调栈的性质，对val栈进行规约：op序列单增不用规约，若非单增，先规约当前栈顶op以及val栈元素再入栈
    -   1+2*3+4
        -   op栈：+*
        -   val栈：123
        -   op入栈：+，破坏了单调栈的性质，此时pop出栈顶，规约23，再入栈
            -   op栈：++
            -   val栈：16（规约）4
            -   表达式结尾，依次规约剩下的元素，1+6+4

-   `instruction cycle()` 
    -   原本打算每条指令的取指、译码，执行阶段和更新rip分开，但好像不太行，会产生越界，并且rsp跟rip指向也非常奇怪
    -   保留在指令阶段更新rip

-   phase-1 总结
    -   一段ADD代码程序编译成机器指令后，cpu执行对应的指令流水线，其中模拟了物理内存`uint8_t mm[]`、虚拟内存（初始化赋值）、寄存器等
    -   进程运行的时候会有自己的虚拟内存空间，同时使用`va2pa()`进行映射
    -   寄存器`reg.xxx`存的值是`vaddr`或`imm`，但他们有属于自己的地址`(uint64_t *)`
    -   访存前需要经过`cache`
    -   `reg.xxx`在操作数结构体中以`uint64_t *`保存，`decode_od()`的时候强转`uint64_t`返回（可能是为了保留**初始化自定义的虚拟地址**），指令执行阶段再解释成`*(uint64_t *)`就可以取值，应该有当简单的方法，但这样可能是为了结构化
