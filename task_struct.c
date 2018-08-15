struct task_struct {

	volatile long state; //˵���˸ý����Ƿ����ִ��.
	//-1��ʾ�������У�0��ʾ���У�����0��ʾֹͣ
	unsigned long flags; //���̱�־,�ڵ���fork()ʱ����

	int sigpending; //�������Ƿ��д��������ź�

	mm_segment_t addr_limit;//���̵�ַ�ռ�,�����ں˽�������ͨ�������ڴ��ŵ�λ�ò�ͬ
                        //0-0xBFFFFFFF for user-thead
                        //0-0xFFFFFFFF for kernel-thread

	volatile long need_resched; //���ȱ�־,��ʾ�ý����Ƿ���Ҫ���µ���,����0,�򵱴��ں�̬���ص��û�̬,�ᷢ������

	int lock_depth; //�����

	long counter; //���̿����е�ʱ����

	long nice; //���̵Ļ���ʱ��Ƭ

	unsigned long policy; //���̵ĵ��Ȳ���,������,ʵʱ����:SCHED_FIFO,SCHED_RR;��ʱ����:SCHED_OTHER;

	struct mm_struct *mm; //�����ڴ������Ϣ

	int processor;



	unsigned long cpus_runnable, cpus_allowed;//�����̲����κ�CPU������, cpus_runnable ��ֵ��0��������1 ���ֵ�����ж��б���ʱ����

	struct list_head run_list; //ָ�����ж��е�ָ��

	unsigned long sleep_time; //���̵�˯��ʱ��

	struct task_struct *next_task, *prev_task; //���ڽ�ϵͳ�����еĽ�������һ��˫��ѭ������,�����init_task.

	struct mm_struct *active_mm;

	struct list_head local_pages; //ָ�򱾵�ҳ��

	unsigned int allocation_order, nr_local_pages;



	struct linux_binfmt *binfmt; //���������еĿ�ִ���ļ��ĸ�ʽ

	int exit_code, exit_signal;

	int pdeath_signal; //��������ֹ�����ӽ��̷��͵��ź�



	unsigned long personality; //Linux��������������UNIX����ϵͳ���ɵķ���iBCS2��׼�ĳ���

	int did_exec : 1; //��POSIXҪ����ƵĲ�����,���ֽ�������ִ�дӸ������м̳еĴ���,����ִ����execveװ����³������

	pid_t pid; //���̱�ʶ��,��������һ������

	pid_t pgrp; //�������ʶ,��ʾ���������Ľ�����

	pid_t tty_old_pgrp; //���̿����ն����ڵ����ʶ

	pid_t session; //���̵ĻỰ��ʶ

	pid_t tgid;


	int leader; //��־,��ʾ�����Ƿ�Ϊ�Ự����

	struct task_struct *p_opptr, *p_pptr, *p_cptr, *p_ysptr, *p_osptr;//ָ��ָ��ԭʼ�ģ������̣����ӽ��̣����Լ�������ֵܽ��̣�                   ���Լ��곤���ֵܽ��� 

	//��p->father�ܱ�p->p_pptr->pid����)

	struct list_head thread_group; //�߳�����

	//����ɢ�б�ָ��

	struct task_struct *pidhash_next; //���ڽ���������HASH��pidhash

	struct task_struct **pidhash_pprev;

	wait_queue_head_t wait_chldexit; //��wait4()ʹ��

	struct completion *vfork_done; // ��vfork() ʹ��

	unsigned long rt_priority; //ʵʱ���ȼ�����������ʵʱ���̵���ʱ��weightֵ


	unsigned long it_real_value, it_prof_value, it_virt_value;

	unsigned long it_real_incr, it_prof_incr, it_virt_value;

	//it_real_value��it_real_incr����REAL��ʱ������λΪjiffies��ϵͳ����it_real_value //���ö�ʱ���ĵ�һ����ֹʱ�䡣�ڶ�ʱ������ʱ������̷���SIGALRM�źţ�ͬʱ����it_real_incr������ֹʱ��

	//it_prof_value��it_prof_incr����Profile��ʱ������λΪjiffies������������ʱ�������ں���״̬�£�ÿ��tick��ʹ

	//it_prof_valueֵ��һ��������0ʱ������̷����ź�SIGPROF��������it_prof_incr����ʱ��

	//it_virt_value��it_virt_value����Virtual��ʱ������λΪjiffies������������ʱ�������ں���״̬�£�ÿ��tick��ʹ

	//it_virt_valueֵ��һ��������0ʱ������̷����ź�SIGVTALRM������it_virt_incr���ó�ֵ��

	//Real��ʱ������ϵͳʱ��ʵʱ���£����ܽ����Ƿ�������

	//Virtual��ʱ��ֻ�ڽ�������ʱ�����ݽ������û�̬���ĵ�ʱ�����

	//Profile��ʱ���ڽ�������ʱ�����ݽ������ĵ�ʱ���������û�̬�����ں�̬������

	struct timer_list real_timer;//ָ��ʵʱ��ʱ����ָ��

	struct tms times; //��¼�������ĵ�ʱ�䣬

	unsigned long start_time;//���̴�����ʱ��

	long per_cpu_utime[NR_CPUS], per_cpu_stime[NR_CPUS]; //��¼������ÿ��CPU�������ĵ��û�̬ʱ��ͺ���̬ʱ��



	//�ڴ�ȱҳ�ͽ�����Ϣ��

	//min_flt, maj_flt�ۼƽ��̵Ĵ�ȱҳ����Copy on��Writeҳ������ҳ������ȱҳ������ӳ���ļ��򽻻��豸�����ҳ��������

	//nswap��¼�����ۼƻ�����ҳ��������д�������豸�ϵ�ҳ������

	//cmin_flt, cmaj_flt, cnswap��¼������Ϊ���ȵ�����������̵��ۼƴ�ȱҳ������ȱҳ���ͻ���ҳ�������ڸ�����

	//������ֹ���ӽ���ʱ�������̻Ὣ�ӽ��̵���Щ��Ϣ�ۼƵ��Լ��ṹ����Щ����

	unsigned long min_flt, maj_flt, nswap, cmin_flt, cmaj_flt, cnswap;

	int swappable : 1; //��ʾ���̵������ַ�ռ��Ƿ���������

	///������֤��Ϣ

	//uid,gidΪ���иý��̵��û����û���ʶ�������ʶ����ͨ���ǽ��̴����ߵ�uid��gid //euid��egidΪ��Чuid,gid

	//fsuid��fsgidΪ�ļ�ϵͳuid,gid��������ID��ͨ������Чuid,gid��ȣ��ڼ������ļ�ϵͳ�ķ���Ȩ��ʱʹ�����ǡ�

	//suid��sgidΪ����uid,gid

	uid_t uid, euid, suid, fsuid;

	gid_t gid, egid, sgid, fsgid;

	int ngroups; //��¼�����ڶ��ٸ��û�����

	gid_t groups[NGROUPS]; //��¼�������ڵ���

	kernel_cap_t cap_effective, cap_inheritable, cap_permitted;//���̵�Ȩ�ܣ��ֱ�����Чλ���ϣ��̳�λ���ϣ�����λ����

	int keep_capabilities : 1;

	struct user_struct *user;



	struct rlimit rlim[RLIM_NLIMITS]; //�������ص���Դ������Ϣ

	unsigned short used_math; //�Ƿ�ʹ��FPU

	char comm[16]; //�����������еĿ�ִ���ļ���

	//�ļ�ϵͳ��Ϣ

	int link_count, total_link_count;

	struct tty_struct *tty;

	unsigned int locks;

	//���̼�ͨ����Ϣ

	struct sem_undo *semundo; //�������źŵ��ϵ�����undo����

	struct sem_queue *semsleeping; //��������Ϊ�źŵƲ���������ʱ�����ڸö����м�¼�ȴ��Ĳ���

	//���̵�CPU״̬���л�ʱ��Ҫ���浽ֹͣ���̵�

	task_struct��

	struct thread_struct thread;



	struct fs_struct *fs;

	//���ļ���Ϣ

	struct files_struct *files;

	//�źŴ�������

	spinlock_t sigmask_lock;

	struct signal_struct *sig; //�źŴ���������

	sigset_t blocked; //���̵�ǰҪ�������źţ�ÿ���źŶ�Ӧһλ

	struct sigpending pending; //�������Ƿ��д��������ź�

	unsigned long sas_ss_sp;

	size_t sas_ss_size;

	int(*notifier)(void *priv);

	void *notifier_data;

	sigset_t *notifier_mask;



	u32 parent_exec_id;

	u32 self_exec_id;



	spinlock_t alloc_lock;



	void *journal_info;

}