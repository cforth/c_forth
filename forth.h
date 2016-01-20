#define     CELL        long  //�����������ͣ���32λ��64λϵͳ����ָ�����͵Ŀ����ͬ
#define     STACK_LEN   1024  //����ջ�����
#define     WIDTH       100   //�ʵ����ֵ���󳤶�
#define     BUFF_LEN    1024

#define DEBUG 0
#if DEBUG
    #define PRINT(fmt, args...) printf(fmt,##args);
#else
    #define PRINT(fmt, args...)
#endif


//��������ָ��
typedef void(*fnP)();  


//�ýṹ�嶨��Forth�Ĵʽṹ����������ʵ�ִʵ�
typedef struct Word
{
    struct Word *link;     //Forth�ʵ�������
    CELL type;             //Forth�����ʱ��
    char *name;            //Forth�ʵ�������
    fnP code_p;            //Forth�ʵĴ�����ָ��
    struct Word **wplist;  //Forth�ʵĲ�����
} Word;


//�����ֵ�ṹ
typedef struct Dict
{
    CELL size;
    Word *head;
} Dict;


//Forthϵͳ����ʱ�ĺ���ָ��
char cmdstr[BUFF_LEN];       //Forth�����ı�������
char *current_text;          //��ǰForth�ʵĴ���ָ��
char *text_p;                //Forth�����ı�ָ��
Dict *forth_dict;            //Forth�ʵ�ָ��
CELL DS[STACK_LEN];          //����ջ
CELL RS[STACK_LEN];          //����ջ
CELL *DP, *RP;               //ջָ��
Word *IP_list[BUFF_LEN];     //ָ���б�����ΪBUFF_LEN/4   
Word **IP;                   //ָ���б�ָ��(ָ���ָ��)
Word **IP_head;              //����ָ���б��ָ��λ��
Word *define_p;              //�����ڴʵ��е�ǰ�������չ��ָ�룬����֧�ֵݹ��myself

//�ı�����
int CheckBlank(char c);
char *ParseWord();

//Forth�ʵĶ��庯��
Word *create(char*name, fnP  fp);
void colon_code();
void does(Word *c, Word **list, int n); //������չ���е�wplist

//Forth�ʵ�Ľӿں���
Dict *dict_init();
int dict_ins_next(Dict *dict, Word *word);
Word *dict_search_name(Dict *dict, char *name);

void explain(); //IP�б�ִ��
int is_num(char *s); //�ж��ַ����Ƿ�Ϊ����
int find(char *name, Dict *dict); //���ݴ�����ȥִ����Ӧ��IP�б����

//Forthջ��������
void empty_stack();
void stack_error(int n);
void ip_push(Word *w);  //IPջPUSH
void ds_push(CELL n);
void rs_push(CELL n);
CELL ds_pop();
CELL rs_pop();
CELL ds_top();
CELL rs_top();

//Forth���Ĵ�
void push();     // push
void popds();    // .
void bye();      // bye

void ret();      // ret

void depth();    // depth
void add();      // +
void sub();      // -
void mul();      // *
void divv();     // /

void drop();     // drop
void showds();   // .s
void pick();     // pick
void roll();     // roll

void invar();     // !
void outvar();    // @

void equal();     // =
void noequal();   // <>
void morethan();  // >
void lessthan();  // <

void if_branch();  // ?branch
void branch();     // branch

void __do();       // (do)
void __loop();     // (loop)

void tor();      // >r
void rto();      // r>
void rat();      // r@

void emit();      // emit

void myself();    // myself
void words();     // words

//Forth���Ĵ��е�������
void immediate();  // immediate
void defcolon();   // :
void endcolon();   // ;
void _if();        // if
void _else();      // else
void _then();      // then
void _do();        // do
void _loop();      // loop
void see();        // see
void forget();     // forget
void var();        // variable
void cons();       // constant


//Forth����������
void interpret();
int load_file(char *file_path);
void load();