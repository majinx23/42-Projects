
#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/incl/libft.h"

# include <dirent.h>
# include <time.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <limits.h>

# define LS_A 1
# define LS_L 2
# define LS_RR 4
# define LS_R 8
# define LS_T 16
# define LS_D 32

enum
{
	ERRNO,
	USAGE,
	MALL_ERR
};

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

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
}						t_file;

int						ls_error(int error, char *str);
t_file					*lst_swap(t_file *p1, t_file *p2);
int						free_files_list(t_file **begin);
int						get_fields_size(t_file *begin, int size[6],
										int *total);
int						get_options(int ac, char **av, int *options);
int						sort_list(t_file **begin, int options);
void					only_files(t_file **begin);
int						print_list(t_file **begin, int options);
int						add_new_file(char path[PATH_MAX], char *name,
										t_file **begin);
int						ft_sort_tab(char **tab, int size,
										int (*f)(const char*, const char*));
int						print_folders(t_file *begin, int options,
										t_bool recursive, int no_files);
int						print_long_format(t_file *file, int size[5]);

#endif
