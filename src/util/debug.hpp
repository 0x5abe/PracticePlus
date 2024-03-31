#ifdef DEBUG
    #define getRefCount(obj) *(unsigned int*)((unsigned int)obj+0x10)
#endif