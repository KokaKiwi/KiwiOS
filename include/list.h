#ifndef LIST_H_
#define LIST_H_

#include "stddef.h"

struct list_head
{
    struct list_head *prev, *next;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

#define list_entry(ptr, type, member) container_of(ptr, type, member)
#define list_first_entry(ptr, type, member) list_entry((ptr)->next, type, member)

#define list_for_each(pos, head) for(pos = (head)->next; pos != (head); pos = pos->next)
#define list_for_each_prev(pos, head) for(pos = (head)->prev; pos != (head); pos = pos->prev)

#define list_for_each_entry(pos, head, member)              \
    for (pos = list_entry((head)->next, typeof(*pos), member);  \
        &pos->member != (head);    \
        pos = list_entry(pos->member.next, typeof(*pos), member))
#define list_for_each_entry_reverse(pos, head, member)          \
    for (pos = list_entry((head)->prev, typeof(*pos), member);  \
        &pos->member != (head);    \
        pos = list_entry(pos->member.prev, typeof(*pos), member))

inline void INIT_LIST_HEAD(struct list_head *);

inline void list_add(struct list_head *, struct list_head *);
inline void list_add_tail(struct list_head *, struct list_head *);
inline void list_del(struct list_head *);
inline void list_replace(struct list_head *, struct list_head *);
inline void list_del_init(struct list_head *);
inline void list_move(struct list_head *, struct list_head *);
inline void list_move_tail(struct list_head *, struct list_head *);
inline int list_is_last(struct list_head *, struct list_head *);
inline int list_empty(const struct list_head *);
inline void list_rotate_left(struct list_head *);
inline int list_is_singular(const struct list_head *);
inline void list_cut_position(struct list_head *, struct list_head *, struct list_head *);
inline void list_splice(const struct list_head *, struct list_head *);
inline void list_splice_tail(const struct list_head *, struct list_head *);
inline size_t list_length(const struct list_head *);

#endif