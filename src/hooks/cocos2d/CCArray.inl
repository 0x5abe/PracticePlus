template <typename T>
void PPCCArray::load(InputStream& i_stream) {
    removeAllObjects();
    unsigned int l_size;
    i_stream >> l_size;
    T* l_objects = reinterpret_cast<T*>(malloc(l_size*sizeof(T)));
    geode::log::info("CCARRAY SIZE in: {}", l_size);
    for (int i = 0; i < l_size; i++) {
        reinterpret_cast<T*>(l_objects)->load(i_stream); 
        addObject(l_objects);
        l_objects++;
    }
}

template <typename T>
void PPCCArray::save(OutputStream& o_stream) {
    unsigned int l_size = count();
    o_stream << l_size;
    geode::log::info("CCARRAY SIZE out: {}", l_size);
    for (int i = 0; i < l_size; i++) {
       reinterpret_cast<T*>(objectAtIndex(i))->save(o_stream); 
    }
}