
return_type chaos_time_to_fat_date_n_time (
  time_type chaos_time UNUSED,
  fat_date_type *fat_date,
  fat_time_type *fat_time)
{
  fat_date->year = 0;
  fat_date->month = 0;
  fat_date->day = 0;

  fat_time->hours = 0;
  fat_time->minutes = 0;
  fat_time->seconds = 0;

  return VFAT_RETURN_SUCCESS;
}

return_type fat_date_n_time_to_chaos_time (
  fat_date_type *fat_date UNUSED,
  fat_time_type fat_time UNUSED,
  time_type *chaos_time)
{
  chaos_time = 0;

  return VFAT_RETURN_SUCCESS;
}
