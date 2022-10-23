/*****  z31.c	  Memory Allocator	**************************************/
extern	void	  DebugRegisterUsage(int typ, int delta_num, int delta_size);
extern	void	  DebugMemory(void);
extern	void	  MemInit(void);
extern	OBJECT	  GetMemory(int siz, FILE_POS *pos);
extern	OBJECT	  zz_free[];
extern	unsigned char	zz_lengths[];
extern	int	  zz_newcount;
extern	int	  zz_disposecount;
extern	int	  zz_listcount;
extern	OBJECT	  zz_hold;
extern	OBJECT	  zz_tmp;
extern	OBJECT	  zz_res;
extern	int	  zz_size;
extern	OBJECT	  xx_link, xx_tmp;
extern	OBJECT	  xx_hold, xx_res;

