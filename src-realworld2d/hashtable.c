#include "hashtable.h"

static const gint32 RANDOM_MAGIC_TAIL = 1;
static const gint32 RANDOM_MAGIC_FACTOR = 2;
static const gint32 RANDOM_BOUND = 100;

struct hashnode_ {
    gint32 key;
    void *data;

    hashnode *prev;
    hashnode *next;
};

void
hashnode_assign(hashnode *n, gint32 key, void *data, hashnode *prev, hashnode *next) {
    n->key = key;
    n->data = data;
    n->prev = prev;
    n->next = next;
}

void hashnode_del(hashnode *n, del_func deleter) {
    deleter(n->data);

    n->prev = NULL;
    n->next = NULL;

    GK_DELETE(n);
}

hashtable *
hashtable_new(gint32 size) {
    GK_ASSERT(size >= 0);

    hashtable *ret = NULL;
    GK_NEW(ret, hashtable);

    ret->size = size;
    ret->cur_count = 0;

    GK_MALLOC(ret->nodes, hashnode*, size);

    return ret;
}

void
hashtable_del(hashtable *ht, del_func deleter) {
    GK_ASSERT(ht);

    hashnode *p = NULL;
    hashnode *tmp = NULL;

    gint32 i = 0;
    for (; i < ht->size; ++i) {
        p = ht->nodes[i];

        if (NULL == p) {
            continue;
        }

        while (p->next) {
            p = p->next;
        }

        while (p->prev) {
            tmp = p;
            hashnode_del(tmp, deleter);

            p = p->prev;
        }
        hashnode_del(p, deleter);
    }

    GK_DELETE(ht->nodes);
    GK_DELETE(ht);
}

gbool
__hashnode_insert_by_key(hashtable *t, gint32 key, void *data) {
    GK_ASSERT(t);
    GK_ASSERT(data);

    hashnode *p = NULL;
    hashnode *prev = NULL;
    gint32 key_in_bucket = key % t->size;

    if (NULL != hashtable_search(t, key)) {
        GK_MSG("Key %d already exists.", key);
        return GKFALSE;
    }

    if (NULL == t->nodes[key_in_bucket]) {      // no nodes in bucket
        GK_NEW(p, hashnode);
        hashnode_assign(p, key, data, NULL, NULL);

        t->nodes[key_in_bucket] = p;
        ++t->cur_count;

        return GKTRUE;
    }

    p = t->nodes[key_in_bucket];
    if (NULL == p->prev && NULL == p->next) {   // only one node in bucket
        prev = p;
    } else {
        while (NULL != p->next) {
            prev = p;
            p = p->next;
        }
        GK_NEW(p, hashnode);
        hashnode_assign(p, key, data, prev, NULL);

        GK_ASSERT(prev);
        prev->next = p;
    }

    ++t->cur_count;

    return GKTRUE;
}

gint32 __hashtable_get_random_key(hashtable *t) {
    gint32 key = GK_RANDOM_INT(0, RANDOM_BOUND);

    do {
        key = key * RANDOM_MAGIC_FACTOR + RANDOM_MAGIC_TAIL;
        if (NULL == hashtable_search(t, key)) {
            break;
        }
    } while (GKTRUE);

    return key;
}

gint32 hashtable_insert(hashtable *ht, void *data) {
    GK_ASSERT(ht);
    GK_ASSERT(data);

    gint32 key = __hashtable_get_random_key(ht);
    __hashnode_insert_by_key(ht, key, data);

    return key;
}

hashnode *
__hashtable_search_node(hashtable *t, gint32 key) {
    GK_ASSERT(t);
    GK_ASSERT(t->size);

    hashnode *p = NULL;

    p = t->nodes[key % t->size];
    if (NULL == p) {
        return NULL;
    }

    while (p) {
        if (key == (p->key)) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

void *
hashtable_search(hashtable *ht, gint32 key) {
    hashnode *node = __hashtable_search_node(ht, key);

    if (NULL == node) {
        return NULL;
    }

    return node->data;
}

gbool hashtable_remove(hashtable *ht, gint32 key, del_func deleter) {
    GK_ASSERT(ht);

    hashnode *p = __hashtable_search_node(ht, key);

    if (NULL == p) {
        GK_WARNING("Key %d not found.", key);
        return GKFALSE;
    }

    if (NULL == p->prev && NULL == p->next) {
        ht->nodes[key % ht->size] = NULL;
    } else {
        if (NULL != p->prev) {
            p->prev->next = p->next;
        }

        if (NULL != p->next) {
            p->next->prev = p->prev;
        }
    }

    hashnode_del(p, deleter);
    p = NULL;
    --ht->cur_count;

    return GKTRUE;
}

#undef main
int main(int argc, char *argv[]) {
    hashtable *ht = hashtable_new(30);
    GK_ASSERT(0 == ht->cur_count);

    GK_UNUSED_PARAM(argc);
    GK_UNUSED_PARAM(argv);

    gint32 data = 1003333;
    gint32 key = hashtable_insert(ht, &data);
    GK_ASSERT(data == *(gint32*)hashtable_search(ht, key));
    GK_ASSERT(1 == ht->cur_count);

    char *str = "hello";
    gint32 key2 = hashtable_insert(ht, str);
    GK_ASSERT(2 == ht->cur_count);
    GK_ASSERT(0 == strcmp(str, (char*)hashtable_search(ht, key2)));

    printf("%d\t%d\n", key, key2);

    GK_ASSERT(GKTRUE == hashtable_remove(ht, key2, GK_DELETE));
    GK_ASSERT(1 == ht->cur_count);

    char *str3 = "test";
    int key3 = hashtable_insert(ht, str3);
    GK_ASSERT(2 == ht->cur_count);
    GK_ASSERT(0 == strcmp(str3, (char*)hashtable_search(ht, key3)));

    puts((char*)hashtable_search(ht, key3));

    GK_ASSERT(GKTRUE == hashtable_remove(ht, key2, GK_DELETE));
    GK_ASSERT(1 == ht->cur_count);

    GK_ASSERT(GKTRUE == hashtable_remove(ht, key, GK_DELETE));
    GK_ASSERT(0 == ht->cur_count);

    hashtable_del(ht, GK_DELETE);

    return 0;
}
