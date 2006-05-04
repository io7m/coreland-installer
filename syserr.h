#ifndef SYSERR_H
#define SYSERR_H

struct syserr {
  struct syserr *w;
  const char *x;
  const char *y;
  const char *z;
};

extern struct syserr syserr_sys;
extern void syserr_init(void);

extern const char *syserr(struct syserr *);
extern void syserr_warn(const char *, const char *, const char *, 
                         const char *, const char *, const char *, struct syserr *);
extern void syserr_die(int, const char *, const char *, const char *, 
                             const char *, const char *, const char *, struct syserr *);

#define SYSERR(r,se,a) \
{ se.who = 0; se.x = a; se.y = 0; se.z = 0; return r; }

#define SYSERR_SYS(r,se,a) \
{ se.who = &syserr_sys; se.x = a; se.y = 0; se.z = 0; return r; }
#define SYSERR_SYS3(r,se,a,b,c) \
{ se.who = &syserr_sys; se.x = a; se.y = b; se.z = c; return r; }

#define syserr_warn6(x1,x2,x3,x4,x5,x6,se) \
syserr_warn((x1),(x2),(x3),(x4),(x5),(x6),(se))
#define syserr_warn5(x1,x2,x3,x4,x5,se) \
syserr_warn((x1),(x2),(x3),(x4),(x5),0,(se))
#define syserr_warn4(x1,x2,x3,x4,se) \
syserr_warn((x1),(x2),(x3),(x4),0,0,(se))
#define syserr_warn3(x1,x2,x3,se) \
syserr_warn((x1),(x2),(x3),0,0,0,(se))
#define syserr_warn2(x1,x2,se) \
syserr_warn((x1),(x2),0,0,0,0,(se))
#define syserr_warn1(x1,se) \
syserr_warn((x1),0,0,0,0,0,(se))

#define syserr_warn6sys(x1,x2,x3,x4,x5,x6) \
syserr_warn((x1),(x2),(x3),(x4),(x5),(x6),&syserr_sys)
#define syserr_warn5sys(x1,x2,x3,x4,x5) \
syserr_warn((x1),(x2),(x3),(x4),(x5),0,&syserr_sys)
#define syserr_warn4sys(x1,x2,x3,x4) \
syserr_warn((x1),(x2),(x3),(x4),0,0,&syserr_sys)
#define syserr_warn3sys(x1,x2,x3) \
syserr_warn((x1),(x2),(x3),0,0,0,&syserr_sys)
#define syserr_warn2sys(x1,x2) \
syserr_warn((x1),(x2),0,0,0,0,&syserr_sys)
#define syserr_warn1sys(x1) \
syserr_warn((x1),0,0,0,0,0,&syserr_sys)

#define syserr_warn6x(x1,x2,x3,x4,x5,x6) \
syserr_warn((x1),(x2),(x3),(x4),(x5),(x6),0)
#define syserr_warn5x(x1,x2,x3,x4,x5) \
syserr_warn((x1),(x2),(x3),(x4),(x5),0,0)
#define syserr_warn4x(x1,x2,x3,x4) \
syserr_warn((x1),(x2),(x3),(x4),0,0,0)
#define syserr_warn3x(x1,x2,x3) \
syserr_warn((x1),(x2),(x3),0,0,0,0)
#define syserr_warn2x(x1,x2) \
syserr_warn((x1),(x2),0,0,0,0,0)
#define syserr_warn1x(x1) \
syserr_warn((x1),0,0,0,0,0,0)

#define syserr_die6(e,x1,x2,x3,x4,x5,x6,se) \
syserr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),(se))
#define syserr_die5(e,x1,x2,x3,x4,x5,se) \
syserr_die((e),(x1),(x2),(x3),(x4),(x5),0,(se))
#define syserr_die4(e,x1,x2,x3,x4,se) \
syserr_die((e),(x1),(x2),(x3),(x4),0,0,(se))
#define syserr_die3(e,x1,x2,x3,se) \
syserr_die((e),(x1),(x2),(x3),0,0,0,(se))
#define syserr_die2(e,x1,x2,se) \
syserr_die((e),(x1),(x2),0,0,0,0,(se))
#define syserr_die1(e,x1,se) \
syserr_die((e),(x1),0,0,0,0,0,(se))

#define syserr_die6sys(e,x1,x2,x3,x4,x5,x6) \
syserr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),&syserr_sys)
#define syserr_die5sys(e,x1,x2,x3,x4,x5) \
syserr_die((e),(x1),(x2),(x3),(x4),(x5),0,&syserr_sys)
#define syserr_die4sys(e,x1,x2,x3,x4) \
syserr_die((e),(x1),(x2),(x3),(x4),0,0,&syserr_sys)
#define syserr_die3sys(e,x1,x2,x3) \
syserr_die((e),(x1),(x2),(x3),0,0,0,&syserr_sys)
#define syserr_die2sys(e,x1,x2) \
syserr_die((e),(x1),(x2),0,0,0,0,&syserr_sys)
#define syserr_die1sys(e,x1) \
syserr_die((e),(x1),0,0,0,0,0,&syserr_sys)

#define syserr_die6x(e,x1,x2,x3,x4,x5,x6) \
syserr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),0)
#define syserr_die5x(e,x1,x2,x3,x4,x5) \
syserr_die((e),(x1),(x2),(x3),(x4),(x5),0,0)
#define syserr_die4x(e,x1,x2,x3,x4) \
syserr_die((e),(x1),(x2),(x3),(x4),0,0,0)
#define syserr_die3x(e,x1,x2,x3) \
syserr_die((e),(x1),(x2),(x3),0,0,0,0)
#define syserr_die2x(e,x1,x2) \
syserr_die((e),(x1),(x2),0,0,0,0,0)
#define syserr_die1x(e,x1) \
syserr_die((e),(x1),0,0,0,0,0,0)

#endif
