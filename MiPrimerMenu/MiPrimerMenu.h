
typedef struct menu_t menu;

struct menu_t{
  char texto[16];
  char abbr;
  void (*i)();
  void (*s)();
  menu *l;
  menu *u;
  menu *d;
  menu *r;
};
