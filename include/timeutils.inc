/**
 * timeutils version 2.0.0 by Manuel Schnitzer
 *
 * https://github.com/mschnitzer/time
 */

native time_convert(timestamp, format[], out[], out_len = sizeof(out));

// datetime functions
native datetime(out[], out_len = sizeof(out));
native timestamp_to_datetime(timestamp, out[], out_len = sizeof(out));
native datetime_to_timestamp(datetime[]);

// date functions
native date(out[], out_len = sizeof(out));
native datetime_to_date(datetime[], out[], out_len = sizeof(out));
native date_to_datetime(date[], out[], out_len = sizeof(out));
native date_to_timestamp(date[]);
native timestamp_to_date(timestamp, out[], out_len = sizeof(out));
