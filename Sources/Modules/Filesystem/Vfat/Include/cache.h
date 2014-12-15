
typedef struct
{
    void *base_address;
} cache_segment_t;

extern return_t cache_request_segment (
  uint32_t file_offset,
  uint32_t file_length,
  void **base_address,
  bool *up_to_date,
  cache_segment_t **cache_segment);
  
extern return_t cache_release_segment (
  cache_segment_t *cache_segment,
  bool valid);  
