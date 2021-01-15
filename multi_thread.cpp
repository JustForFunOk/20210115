// 现有两个 producer线程 A和 B负责生产数据
//（A线程生产的数据是结构体 A_struct，A_struct.a是随机产生的 1 到 100间的一个整数,
// B线程生产的数据是结构体 B_struct，B_struct.data是随机产生的 0 到 1之间 的 5个小数（精确到小数点后 2位））。
// 一个 consumer线程 C负责计算最新收取的 B_struct.data中数据的加和 sum_b，
// sum_b满足当最新收取的 A_struct.a数据为奇数时,sum_b取正，当最新收取的 A_struct.a数据为偶数时，sum_b取负。
// 如果连续来的数据都为 B_struct时，sum_b的正负由最近一次收取到的 A_struct.a的奇偶决定。
// 线程 C会实时维护一个累计 sum_b的加和 sum_b_all。
// 最后线程 D每隔 1秒钟打印一次当前 sum_b_all的值。
// 请设计程序，使得线程间通讯的延迟最小。
// A_struct和 B_struct定义如下：
// structA_struct{
//     int a;
// }
// structB_struct{
//     double data[5];
// }
// c++ 14