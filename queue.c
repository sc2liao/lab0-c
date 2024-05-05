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
    struct list_head *new_head =
        (struct list_head *) malloc(sizeof(struct list_head));
    if (!new_head)
        return NULL;
    INIT_LIST_HEAD(new_head);
    return new_head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    element_t *ele;
    element_t *safe;
    list_for_each_entry_safe (ele, safe, head, list)
        q_release_element(ele);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_ele = (element_t *) malloc(sizeof(element_t));
    if (!new_ele)
        return false;
    size_t str_size = strlen(s);
    new_ele->value = (char *) malloc(sizeof(char) * (str_size + 1));
    if (!new_ele->value) {
        free(new_ele);
        return false;
    }
    strncpy(new_ele->value, s, str_size);
    new_ele->value[str_size - 1] = '\0';
    list_add(&new_ele->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_ele = (element_t *) malloc(sizeof(element_t));
    if (!new_ele)
        return false;
    size_t str_size = strlen(s);
    new_ele->value = (char *) malloc(sizeof(char) * (str_size + 1));
    if (!new_ele->value) {
        free(new_ele);
        return false;
    }
    strncpy(new_ele->value, s, str_size);
    new_ele->value[str_size - 1] = '\0';
    list_add_tail(&new_ele->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *removed_ele = list_entry(head->next, element_t, list);
    strncpy(sp, removed_ele->value, bufsize - 1);
    sp[bufsize - 1] = '\0';
    list_del_init(&removed_ele->list);
    return removed_ele;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *removed_ele = list_entry(head->prev, element_t, list);
    strncpy(sp, removed_ele->value, bufsize - 1);
    sp[bufsize - 1] = '\0';
    list_del_init(&removed_ele->list);
    return removed_ele;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;
    int q_szie = 0;
    struct list_head *node;
    list_for_each (node, head) {
        q_szie++;
    }
    return q_szie;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;
    if (list_is_singular(head)) {
        element_t *del_ele = list_entry(head->next, element_t, list);
        q_release_element(del_ele);
        return true;
    }
    struct list_head *node, *safe;
    struct list_head *fast = head->next->next;

    list_for_each_safe (node, safe, head) {
        fast = fast->next->next;
        if (fast == head || fast == head->next) {
            element_t *del_ele = list_entry(node, element_t, list);
            q_release_element(del_ele);
        }
    }
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
    struct list_head *node, *safe;
    list_for_each_safe (node, safe, head) {
        struct list_head *tmp = node->next;
        node->next = node->prev;
        node->prev = tmp;
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
