#include <Interfaces/namespace.h>

extern handle_t handle_namespace;

static inline void global_namespace_bind (char *name, handle_t *handle)
{
    namespace$bind (&handle_namespace, name, handle);
}

static inline void global_namespace_rebind (char *old_name, char *new_name)
{
    namespace$rebind (&handle_namespace, old_name, new_name);
}

static inline void global_namespace_resolve (char *name, handle_t *handle)
{
    namespace$resolve (&handle_namespace, name, handle);
}

static inline void global_namespace_unbind (char *name)
{
    namespace$unbind (&handle_namespace, name);
}


