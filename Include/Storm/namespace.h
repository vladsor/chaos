
extern void namespace_bind (context_t *context, char *name, 
    handle_t *handle);
extern void namespace_bind_namespace (context_t *context, char *name, 
    handle_t *handle);
extern void namespace_rebind (context_t *context, 
    char *old_name, char *new_name);
extern void namespace_resolve (context_t *context, char *name,
    handle_t *handle);
extern void namespace_unbind (context_t *context, char *name);

static inline void global_namespace_bind (char *name, handle_t *handle)
{
    namespace_bind (NULL, name, handle);
}

static inline void global_namespace_rebind (char *old_name, char *new_name)
{
    namespace_rebind (NULL, old_name, new_name);
}

static inline void global_namespace_resolve (char *name, handle_t *handle)
{
    namespace_resolve (NULL, name, handle);
}

static inline void global_namespace_unbind (char *name)
{
    namespace_unbind (NULL, name);
}


