
/* Open a file. */
return_t vfs_open (char *filename, vfs_file_mode_t mode, 
                   vfs_file_handle_t *handle);

/* Close a file. */
return_t vfs_close (vfs_file_handle_t handle);

/* Mount the given block device into the given path. */
return_t vfs_mount (char *path, block_service_t *block);

/* Assign a virtual path to a logical. */
return_t vfs_assign (char *virtual, char *logical);

/* Read from a file. */
return_t vfs_read (vfs_file_handle_t handle, void *buffer, 
                   size_t length);

/* Get information about a file. */
return_t vfs_info (char *path, vfs_file_info_t *info);
