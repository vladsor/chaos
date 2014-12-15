#include <enviroment.h>

#include "Include/return_values.h"
#include "Include/cache.h"

return_t cache_request_segment (
  uint32_t file_offset UNUSED,
  uint32_t file_length,
  void **base_address,
  bool *up_to_date,
  cache_segment_t **cache_segment)
{
  memory_allocate ((void **) cache_segment, sizeof (cache_segment_t));
  memory_allocate (base_address, file_length);
  (*cache_segment)->base_address = (*base_address);

  (*up_to_date) = FALSE;

  return VFAT_RETURN_SUCCESS;
}

return_t cache_release_segment (
  cache_segment_t *cache_segment,
  bool valid UNUSED)
{
  memory_deallocate ((void **) &(cache_segment->base_address));
  memory_deallocate ((void **) &cache_segment);

  return VFAT_RETURN_SUCCESS;
}
