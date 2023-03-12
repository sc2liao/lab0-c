#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(*head));
    if (!head)
        return NULL;

    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;
    struct list_head *node, *safe;
    list_for_each_safe (node, safe, l) {
        q_release_element(list_entry(node, element_t, list));
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *obj = malloc(sizeof(element_t));
    if (!obj)
        return false;
    size_t s_len = strlen(s) + 1;
    obj->value = malloc(s_len * sizeof(char));
    if (!obj->value) {
        free(obj);
        return false;
    }
    memcpy(obj->value, s, s_len);
    list_add(&obj->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *obj = malloc(sizeof(element_t));
    if (!obj)
        return false;
    size_t s_len = strlen(s) + 1;
    obj->value = malloc(s_len * sizeof(char));
    if (!obj->value) {
        free(obj);
        return false;
    }
    memcpy(obj->value, s, s_len);
    list_add_tail(&obj->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head)
        return NULL;
    element_t *obj = list_first_entry(head, element_t, list);
    size_t len = strlen(obj->value);
    if (len > bufsize)
        len = bufsize;
    memcpy(sp, obj->value, len);
    list_del(&obj->list);
    return obj;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head)
        return NULL;
    element_t *obj = list_last_entry(head, element_t, list);
    size_t len = strlen(obj->value);
    if (len > bufsize)
        len = bufsize;
    memcpy(sp, obj->value, len);
    list_del(&obj->list);
    return obj;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head)
        return false;
    struct list_head *last = head->prev;
    struct list_head **slow = &head;
    for (struct list_head *fast = head; fast != last; fast = fast->next->next) {
        slow = &(*slow)->next;
    }
    list_del_init(*slow);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head)
        return false;
    const struct list_head *final = head->prev;
    for (struct list_head **curr = &head;
         *curr != final && (*curr)->next != final;) {
        element_t *currobj = list_entry((*curr), element_t, list);
        element_t *nextobj = list_entry((*curr)->next, element_t, list);
        if (memcmp(currobj->value, nextobj->value, strlen(currobj->value))) {
            element_t *tmp = nextobj;
            while (&tmp->list != final &&
                   memcmp(currobj->value, tmp->value, strlen(currobj->value))) {
                list_del(&tmp->list);
                tmp = list_entry(&tmp->list, element_t, list);
            }
            *curr = &tmp->list;
        } else {
            curr = &(*curr)->next;
        }
    }
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head)
        return;
    struct list_head *curr = head->next;
    while (curr != head && curr->next != head) {
        list_move(curr, curr->next);
        curr = curr->next;
    }
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    struct list_head *safe;
    struct list_head *node;
    list_for_each_safe (node, safe, head) {
        list_move(node, head);
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
