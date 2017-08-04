#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "globaldefs.h"

GK_BEGIN_HEADER

typedef struct hashnode_ hashnode;  // private implemention

typedef struct hashtable_ {
    gint32 size;
    gint32 cur_count;

    hashnode **nodes;
} hashtable;

typedef void *del_func(void *);

///
/// \brief  Generate a new hashtable.
///
/// Typical usage:
/// \code
///                 hashtable *ptr = hashtable_new(20);
/// \endcode
/// \param  size    Size of generated hashtable.
///
/// \return         Pointer of generated hashtable, NULL if fail.
///
hashtable *hashtable_new(gint32 size);

///
/// \brief  Delete an existing hashtable.
///
/// Typical usage:
/// \code
///                 hashtable_del(ht);
/// \endcode
/// \param  ht      Pointer to a hashtable.
///
void hashtable_del(hashtable *ht, del_func deleter);

///
/// \brief  Insert a element into a hashtable.
///
/// Typical usage:
/// \code
///         hashtable_insert(ht, map_data);
/// \endcode
/// \param  ht      Target hashtable.
/// \param  data    Element to be inserted.
///
/// \return         Pointer of key to the element inserted.
///
gint32 hashtable_insert(hashtable *ht, void *data);

///
/// \brief  Search for an element with specified key.
///
/// Typical usage:
/// \code
///         music_ptr = hashtable_search(ht, key);
/// \endcode
/// \param  ht      Target hashtable
/// \param  key     Specified key.
///
/// \return         Pointer of element founded, NULL if fail.
///
void *hashtable_search(hashtable *ht, gint32 key);

///
/// \brief  Remove an element with specified key.
///
/// Typical usage:
/// \code
///         success = hashtable_remove(ht, key);
/// \endcode
/// \param  ht      Target hashtable.
/// \param  key     Specified key.
///
/// \return         Status of remove action, True if success.
///
gbool hashtable_remove(hashtable *ht, gint32 key, del_func deleter);

GK_END_HEADER

#endif // HASHTABLE_H
