
enum
{
    SCENE_TYPE_ASYNCHRONOUS,
    SCENE_TYPE_SYNCHRONOUS
};

extern 
    scene_reference_t 
        scene_create 
        (
            description_reference_t scene_description, 
            uint32_t type, 
            uint32_t capacity
        );
    
extern 
    void 
        scene_destroy 
        (
            scene_reference_t scene_reference
        );

extern 
    void 
        scene_flush 
        (
            scene_reference_t scene_reference
        );

