#ifndef SEARCH_H
#define SEARCH_H

int compareForestTreeRootId (const void * forestListElement, const void * forestLinstEntry);
int compareTreeForestId (const void * , const void *);
int compareForestForestId (const void * forestListElement, const void * forestLinstEntry);
int compareTreeTreeRootId (const void * , const void * );
int searchForestTreeRootId (const void *, const void *);
int searchTreeForestId (const void * , const void * ); 
int searchTreeTreeRootId (const void *, const void *);
int searchForestForestId (const void * , const void * );
int compareForestNHalos (const void *, const void *); 
int compareForest (const void *, const void *);

#endif