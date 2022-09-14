/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author Gengyuan Zhang <gengyuaz@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->curr = q->head;
        q->size = 0;
    }
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL) {
        if (q->curr != q->head) {
            q->curr = q->head;
        }
        list_ele_t *temp = NULL;
        while (q->curr != NULL) {
            free(q->curr->value);
            temp = q->curr->next;
            free(q->curr);
            q->curr = temp;
        }
        free(q);
    }
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {

    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    list_ele_t *new_head;
    new_head = malloc(sizeof(list_ele_t));

    if (new_head == NULL) {
        free(new_head);
        return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    char *copy;
    copy = malloc(sizeof(char) * strlen(s) + 1);

    /* What if either call to malloc returns NULL? */
    if (copy == NULL) {
        free(new_head);
        return false;
    }
    strcpy(copy, s);
    new_head->value = copy;
    new_head->next = q->head;
    q->head = new_head;

    if (q->tail == NULL) {
        q->tail = new_head;
    }

    q->size = q->size + 1;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    list_ele_t *new_tail;
    new_tail = malloc(sizeof(list_ele_t));

    if (new_tail == NULL) {
        free(new_tail);
        return false;
    }
    char *copy;
    copy = malloc(sizeof(char) * strlen(s) + 1);

    if (copy == NULL) {
        free(new_tail);
        return false;
    }

    strcpy(copy, s);
    new_tail->value = copy;
    new_tail->next = NULL;
    q->tail->next = new_tail;
    q->tail = new_tail;

    if (q->head == NULL) {
        q->head = new_tail;
    }
    q->size = q->size + 1;
    return true;
}
/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL) {
        return false;
    }

    if (buf != NULL) {
        size_t i = 0;
        while (i < bufsize - 1) {
            *(buf + i) = *(q->head->value + i);
            i = i + 1;
            if (*(q->head->value + i) == 0) {
                break;
            }
        }
        *(buf + i) = 0;
    }
    q->curr = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = q->curr;
    q->size = q->size - 1;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL) {
        return 0;
    } else {
        return q->size;
    }
}
/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) {
        return;
    } else {
        list_ele_t *temp_head = q->head, *temp_tail = q->tail;
        list_ele_t *temp_pre = NULL, *temp_next = NULL;
        q->curr = q->head;
        while (q->curr != NULL) {
            temp_next = q->curr->next;
            q->curr->next = temp_pre;
            temp_pre = q->curr;
            q->curr = temp_next;
            q->head = temp_tail;
            q->tail = temp_head;
        }
        return;
    }
}
