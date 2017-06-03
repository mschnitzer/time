/**
 * timeutils version 1.1.0 by Manuel Schnitzer
 *
 * https://github.com/mschnitzer/time
 */

native time_convert(timestamp, format[], out[], out_len);
native datetime(out[], out_len);
native timestamp_to_datetime(timestamp, out[], out_len);
native datetime_to_timestamp(datetime[]);

