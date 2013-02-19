#include <list.h>

inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    prev->next = new;

    new->prev = prev;
    new->next = next;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void __list_del_entry(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void __list_cut_position(struct list_head *list, struct list_head *head, struct list_head *entry)
{
    struct list_head *new_first = entry->next;
    list->next = head->next;
    list->next->prev = list;
    list->prev = entry;
    entry->next = list;
    head->next = new_first;
    new_first->prev = head;
}

static inline void __list_splice(const struct list_head *head, struct list_head *prev, struct list_head *next)
{
    struct list_head *first = head->next;
    struct list_head *last = head->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

inline void list_replace(struct list_head *old, struct list_head *new)
{
    new->next = old->next;
    new->next->prev = new;

    new->prev = old->prev;
    new->prev->next = new;
}

inline void list_del_init(struct list_head *entry)
{
    __list_del_entry(entry);
    INIT_LIST_HEAD(entry);
}

inline void list_move(struct list_head *entry, struct list_head *head)
{
    __list_del_entry(entry);
    list_add(entry, head);
}

inline void list_move_tail(struct list_head *entry, struct list_head *head)
{
    __list_del_entry(entry);
    list_add_tail(entry, head);
}

inline int list_is_last(struct list_head *entry, struct list_head *head)
{
    return (entry->next == head);
}

inline int list_empty(const struct list_head *head)
{
    return (head->next == head);
}

inline void list_rotate_left(struct list_head *head)
{
    struct list_head *first;

    if(!list_empty(head))
    {
        first = head->next;
        list_move_tail(first, head);
    }
}

inline int list_is_singular(const struct list_head *head)
{
    return ((!list_empty(head)) && (head->next == head->prev));
}

inline void list_cut_position(struct list_head *list, struct list_head *head, struct list_head *entry)
{
    if (list_empty(head))
    {
        return;
    }
    if (list_is_singular(head) && (head->next != entry && head != entry))
    {
        return;
    }
    if (entry == head)
    {
        INIT_LIST_HEAD(list);
    }
    else
    {
        __list_cut_position(list, head, entry);
    }
}

inline void list_splice(const struct list_head *list, struct list_head *head)
{
    if(!list_empty(list))
    {
        __list_splice(list, head, head->next);
    }
}

inline void list_splice_tail(const struct list_head *list, struct list_head *head)
{
    if (!list_empty(list))
    {
        __list_splice(list, head->prev, head);
    }
}

inline size_t list_length(const struct list_head *head)
{
    size_t length = 0;
    struct list_head *cur = head->next;

    while(cur != head)
    {
        length++;
        cur = cur->next;
    }

    return length;
}