
#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/incl/libft.h"

/*
** ioctl is to get the terminal width
**
*/

# include <dirent.h>
# include <time.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <limits.h>
# include <sys/ioctl.h>

enum	{ERRNO, USAGE, MALL_ERR};

/*
** -a (LS_A) to display hidden files, current folder and previous folder,
** -l (LS_L) to get more details, -d to display current folder only,
** -R (LS_RR) recursively list subfolders encountered,
** -r (LS_R) reverse the order of the sort to get reverse ASCII order or the
** oldest entries first (or largest files last, if combined with sort by size
** -t (LS_T) to display by time creation
** -c (LS_C) to color folders 
** -1 (LS_ONE) to display results on one column, 
*/

# define LS_A	1
# define LS_L	2
# define LS_RR	4
# define LS_R	8
# define LS_T	16
# define LS_D	32
# define LS_G	64
# define LS_ONE 128

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_index
{
	int				y;
	int				x;
}						t_index;

/*
** mode_t is to get file chmod
**
*/

typedef struct			s_file
{
	mode_t			mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	dev_t			st_rdev;
	time_t			time;
	long			ntime;
	blkcnt_t		st_blocks;
	char			*name;
	char			full_path[PATH_MAX];
	struct s_file	*next;
	t_list			list;
}						t_file;


/*
** parsing flags 
*/

int		parsing(int ac, char **av, int *flags);
int		parse_options(char *s, int *flags);
int		ls_error(char *s, int error);

/*
** displaying files
*/

t_file	*init_files_list(char **av, int ac, int first);




void					only_files(t_file **begin);
int						add_new_file(char path[PATH_MAX], char *name, t_file **begin);
int						ft_sort_tab(char **tab, int size,
										int (*f)(const char*, const char*));

/*
** -R flag
*/

int						print_folders(t_file *begin, int options,
										t_bool recursive, int no_files);

/*
** -r and -t flags
*/

int						sort_list(t_file**begin, short flags);
t_file					*reverse_lst(t_file *lst);

/*
** display list
*/

int						display_list(t_file **begin, int options);

/*
**  print list with -l flag
*/

int						display_detailed_list(t_file *begin, int flags);
int						get_row_size(t_file *begin, int size[6], int *total);
int						display_list_items(t_file *file, int size[5], int flags);

/*
** display name with -c color flag
*/

void					display_name(t_file *l, int flags);

/*
** misc.c file functions
*/

t_file					*lst_swap(t_file *p1, t_file *p2);
int						lst_maxlen(t_file *lst);
int						free_list_content(t_file **lst);
int						integer_len(int n);

#endif
