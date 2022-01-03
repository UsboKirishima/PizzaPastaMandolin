
/**
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
    \date 18 Nov 2021
    \file logax.h
*/

#ifndef EXOTIC_LOGAX_H
#define EXOTIC_LOGAX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

#ifndef LOGAX_NO_TIME
#include <time.h>
#endif

#if defined(_WIN32) && defined(LOGAX_USE_OLD_CONSOLE_MODE)
#include <windows.h>
#endif

/** 
    The inline keyword to optimize the function. In 
    C89 and C90 the inline keyword semantic is 
    different from current C standard semantic hence 
    for compilation targeting C89 or C99 the inline 
    keyword is ommited.
*/
#ifdef __STDC_VERSION__
    #define __LOGAX_STDC_VERSION__ __STDC_VERSION__
#else
    #ifdef __cplusplus
        #if __cplusplus > 199711L
            #define __LOGAX_STDC_VERSION__ __cplusplus
        #endif
    #endif
#endif
#ifndef __LOGAX_STDC_VERSION__
    #ifdef __FUNCTION__ 
        #define __LOGAX_FUNCTION__ __FUNCTION__
    #else
        #define __LOGAX_FUNCTION__ "<unknown>"
    #endif
    #define LOGAX_NULL 0L
#else 
    #define __LOGAX_FUNCTION__ __func__
    #define LOGAX_NULL NULL
#endif

#if defined(_WIN32) && defined(LOGAX_USE_OLD_CONSOLE_MODE)

#define LOGAX_RESET_TERMINAL           15                                                /**< reset the terminal color. Nothing          */
#define LOGAX_FOREGROUND_TRACE         11                                                /**< trace terminal foreground color - cyan     */
#define LOGAX_FOREGROUND_DEBUG         2                                                 /**< debug terminal foreground color - green    */
#define LOGAX_FOREGROUND_INFO          5                                                 /**< info terminal foreground color - magenta   */
#define LOGAX_FOREGROUND_WARN          6                                                 /**< warn terminal foreground color - yellow    */
#define LOGAX_FOREGROUND_ERROR         4                                                 /**< error terminal foreground color - red      */
#define LOGAX_FOREGROUND_FATAL         4                                                 /**< fatal terminal foreground color - red      */
#define LOGAX_RESET_TERMINAL_ATTR()    SetConsoleTextAttribute(logax_hConsole, logax_default_color); /**< reset the terminal color                   */

#else

#define LOGAX_RESET_TERMINAL           "\x1B[0m"                                         /**< reset the terminal color                   */
#define LOGAX_FOREGROUND_TRACE         "\x1B[36m"                                        /**< trace terminal foreground color - cyan     */
#define LOGAX_FOREGROUND_DEBUG         "\x1B[32m"                                        /**< debug terminal foreground color - green    */
#define LOGAX_FOREGROUND_INFO          "\x1B[35m"                                        /**< info terminal foreground color - magenta   */
#define LOGAX_FOREGROUND_WARN          "\x1B[33m"                                        /**< warn terminal foreground color - yellow    */
#define LOGAX_FOREGROUND_ERROR         "\x1B[31m"                                        /**< error terminal foreground color - red      */
#define LOGAX_FOREGROUND_FATAL         "\x1B[31m"                                        /**< fatal terminal foreground color - red      */
#define LOGAX_RESET_TERMINAL_ATTR()    fprintf(stream, "%s", LOGAX_RESET_TERMINAL)       /**< reset the terminal color                   */

#endif

#ifndef LOGAX_LOGGER_NO_CALLBACK
/**
    
*/
#ifndef LOGAX_MAX_CALLBACKS
#define LOGAX_MAX_CALLBACKS 5
#endif

/**
    This is the function signature of the callback, any function defined with same signature 
	can be registered with the LogaxLogger as callback which will be invoked if a new logevent is 
	sent.
*/
typedef void (*logax_callback)(const char *date, const char *time, const int level, const char *file, const size_t line_number, const char *function_name, const char *fmt, ...);
#endif

/**
    More bit location is reserved till 15 to accomodate new options without breaking 
	backward compatibility
*/
enum LogaxOption {
    LOGAX_OPTION_QUITE           = 1 << 1, /**< the option to disable writing to output stream */
#ifndef LOGAX_NO_TIME
    LOGAX_OPTION_DATE            = 1 << 2, /**< option to write/set the date of the log event */
    LOGAX_OPTION_TIME            = 1 << 3, /**< option to set the time of the log event */
    LOGAX_OPTION_DATE_TIME       = 1 << 4, /**< the option to set both the date and time of the log event */
#endif
    LOGAX_OPTION_FILE_PATH       = 1 << 5, /**< option to set the full path to the file where the log event was sent from */
    LOGAX_OPTION_FILE_NAME_ONLY  = 1 << 6, /**< option to set only the name of the file where the log event was sent from */
    LOGAX_OPTION_LINE_NUMBER     = 1 << 7, /**< option to set the line number where the log even was sent */
#ifndef LOGAX_NO_COLORING
    LOGAX_OPTION_COLORED         = 1 << 8, /**< this option is used to enable preety print and colored outputs */
#endif
    LOGAX_OPTION_FUNCTION        = 1 << 9, /**< option to write/set the name of the function where the log was set from */
    LOGAX_OPTION_ALL             = 1 << 15 /**< this option enables all the other options above apart from LOGAX_OPTION_QUITE */
};

/**
    The options to classify the log event by level
*/
enum LogaxLevel {
    LOGAX_LEVEL_TRACE   = 1 << 16, /**< Mark the log event as trace */
    LOGAX_LEVEL_DEBUG   = 1 << 17, /**< Mark the log event as debug */
    LOGAX_LEVEL_INFO    = 1 << 18, /**< Mark the log event as an information */
    LOGAX_LEVEL_WARN    = 1 << 19, /**< Mark the log event as a warning */
    LOGAX_LEVEL_ERROR   = 1 << 20, /**< Mark the log event as an error */
    LOGAX_LEVEL_FATAL   = 1 << 21  /**< Mark the log event as a critical error */
};

/**
    Get the string name of the log level.
*/
#define GET_LEVEL_STRING(level) ((level == LOGAX_LEVEL_TRACE) ? "TRACE" :\
	(level == LOGAX_LEVEL_DEBUG) ? "DEBUG" :\
	(level == LOGAX_LEVEL_INFO) ? "INFO" :\
	(level == LOGAX_LEVEL_WARN) ? "WARN" :\
	(level == LOGAX_LEVEL_ERROR) ? "ERROR" :\
	(level == LOGAX_LEVEL_FATAL) ? "FATAL" : "")

/**
    The options to specify the format of the log output
*/
enum LogaxFormatter {
    LOGAX_FORMATTER_TEXT         = 1 << 25, /**< Format the log output as plain string */
    LOGAX_FORMATTER_KEY_VALUE    = 1 << 26, /**< Format the log output as a key value entries */
    LOGAX_FORMATTER_JSON         = 1 << 27  /**< Format the log output as a valid JSON object */
};

/**
    The struct that can be used to share stream and flags across log events.
	The fields are optionals. If the macro **LOGAX_NO_OUTPUT_STREAM** is defined 
	the output_stream field will not be compiled, and if the macro **LOGAX_LOGGER_NO_CALLBACK** 
	is defined all callback related operatioon will be disabled in the library.
*/
struct logax_logger_s {
    int flags;                /**< The field that holds the flags/option bits */
#if !defined(LOGAX_NO_OUTPUT_STREAM)
    FILE *output_stream;        /**< The FILE* stream to write the log events */
#endif
#ifndef LOGAX_LOGGER_NO_CALLBACK
    logax_callback callbacks[LOGAX_MAX_CALLBACKS]; /**< The array that holds the callbacks that was registered to self logax_logger_s */
#endif
};

/**
*/
typedef struct logax_logger_s LogaxLogger;

/**
*/
static void logax_init_logger(LogaxLogger *logax_logger) {
    int index = 0;
    logax_logger->flags = LOGAX_FORMATTER_TEXT | LOGAX_OPTION_FILE_NAME_ONLY | LOGAX_OPTION_LINE_NUMBER;
#ifndef LOGAX_NO_COLORING
    logax_logger->flags |= LOGAX_OPTION_COLORED;
#endif
#ifndef LOGAX_NO_TIME
    logax_logger->flags |= LOGAX_OPTION_DATE_TIME;
#endif
#if defined(stdout) && !defined(LOGAX_NO_OUTPUT_STREAM)
    logax_logger->output_stream = stdout;
#endif
#ifndef LOGAX_LOGGER_NO_CALLBACK
    for (; index < LOGAX_MAX_CALLBACKS; index++) {
        logax_logger->callbacks[index] = LOGAX_NULL;
    }
#endif
}

#if !defined(LOGAX_NO_OUTPUT_STREAM)
/**
*/
static void logax_init_logger_ws(LogaxLogger *logax_logger, FILE *output_stream) {
    int index = 0;
    logax_logger->flags = LOGAX_FORMATTER_TEXT | LOGAX_OPTION_FILE_NAME_ONLY | LOGAX_OPTION_LINE_NUMBER;
#ifndef LOGAX_NO_COLORING
    logax_logger->flags |= LOGAX_OPTION_COLORED;
#endif
#ifndef LOGAX_NO_TIME
    logax_logger->flags |= LOGAX_OPTION_DATE_TIME;
#endif
    logax_logger->output_stream = output_stream;
#ifndef LOGAX_LOGGER_NO_CALLBACK
    for (; index < LOGAX_MAX_CALLBACKS; index++) {
        logax_logger->callbacks[index] = LOGAX_NULL;
    }
#endif
}
#endif

#ifndef LOGAX_LOGGER_NO_CALLBACK
/**
*/
static unsigned logax_logger_add_callback(LogaxLogger *logax_logger, logax_callback callback) {
    int index = 0;;
    for (; index < LOGAX_MAX_CALLBACKS; index++) {
        if (logax_logger->callbacks[index] == LOGAX_NULL) {
            logax_logger->callbacks[index] = callback;
            return index;
        }
    }
    return -1;
}
#else
#define logax_logger_add_callback(logax_logger, callback)
#endif

/**
*/
#define logax_add_flag(flags, flag) flags |= flag;

/**
*/
#define logax_set_flag logax_add_flag

/**
*/
#define logax_remove_flag(flags, flag) flags &= ~flag;

/**
*/
#define logax_clear_flag logax_remove_flag

/**
*/
#define logax_set_formatter(logax_logger, new_formatter) {\
        if ((logax_logger)->flags & LOGAX_FORMATTER_TEXT) logax_remove_flag((logax_logger)->flags, LOGAX_FORMATTER_TEXT);\
        if ((logax_logger)->flags & LOGAX_FORMATTER_KEY_VALUE) logax_remove_flag((logax_logger)->flags, LOGAX_FORMATTER_KEY_VALUE);\
        if ((logax_logger)->flags & LOGAX_FORMATTER_JSON) logax_remove_flag((logax_logger)->flags, LOGAX_FORMATTER_JSON);\
        logax_add_flag((logax_logger)->flags, new_formatter);\
    }

/**
*/
#define logax_set_quite(logax_logger, make_quite) {\
        if (!make_quite && ((logax_logger)->flags & LOGAX_OPTION_QUITE)) { logax_remove_flag((logax_logger)->flags, LOGAX_OPTION_QUITE); }\
        else if (make_quite && !((logax_logger)->flags & LOGAX_OPTION_QUITE)) { logax_add_flag((logax_logger)->flags, LOGAX_OPTION_QUITE); }\
    }

#ifndef LOGAX_NO_OUTPUT_STREAM
/*
*/
static size_t logax_cstr_length(char char_array[]) {
    size_t length = 0;
    if (char_array == LOGAX_NULL) { return length; }
    while(char_array[length] != '\0') {
        length++;
    }
    return length;
}

/**
*/
static void logax_replace_char(char const* const file_path, char formatted_file_name[], char old_char, char new_char) {
    unsigned i = 0, j = -1;
    while (file_path[i] != '\0') {
        if (file_path[i] == old_char) {
            formatted_file_name[i] = new_char;
        } else {
            formatted_file_name[i] = file_path[i];
        }
        ++i;
    }
    formatted_file_name[i] = '\0';
}

/**
*/
static void logax_extract_name_only(char const* const file_path, char formatted_file_name[]) {
    unsigned i = 0, j = -1;
    while (file_path[i] != '\0') {
        if (file_path[i] == '\\' || file_path[i] == '/') {
            j = 0;
        } else if (j != -1) {
            formatted_file_name[j] = file_path[i];
            j++;
        }
        ++i;
    }
    formatted_file_name[j] = '\0';
}

#if defined(_WIN32) && defined(LOGAX_USE_OLD_CONSOLE_MODE)
int logax_default_color = LOGAX_RESET_TERMINAL;
int initialized_h_console = 0;
HANDLE logax_hConsole;

/**
*/
#define LOGAX_INITIALIZE_HCONSOLE() if (!initialized_h_console) {\
		CONSOLE_SCREEN_BUFFER_INFO info;\
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {\
			logax_default_color = info.wAttributes;\
		}\
		logax_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
		initialized_h_console = 1;\
	}

#ifndef LOGAX_NO_COLORING
#define LOGAX_DELEGATE_FPRINT_STR(foreground, text) if (is_colored) { SetConsoleTextAttribute(logax_hConsole, foreground); } fprintf(stream, "%s", text); if (is_colored) { LOGAX_RESET_TERMINAL_ATTR(); }
#define LOGAX_DELEGATE_FPRINT_SIZE_T(foreground, text) if (is_colored) { SetConsoleTextAttribute(logax_hConsole, foreground); } fprintf(stream, "%zu", text); if (is_colored) {LOGAX_RESET_TERMINAL_ATTR(); }
#else
#define LOGAX_DELEGATE_FPRINT_STR(foreground, text) fprintf(stream, "%s", text);
#define LOGAX_DELEGATE_FPRINT_SIZE_T(foreground, text) fprintf(stream, "%zu", text);
#endif

#ifndef LOGAX_NO_COLORING
/**
*/
#define LOGAX_WRITE_COLOR_CODE(color) SetConsoleTextAttribute(logax_hConsole, color);
#else
#define LOGAX_WRITE_COLOR_CODE(color)
#endif

/**
*/
#define LOGAX_WRITE_LEVEL_COLOR__INTERNALL__(prefix_value, level, suffix_value)\
	if (is_colored) {\
		fprintf(stream, "%s", prefix_value); LOGAX_DELEGATE_FPRINT_STR(LOGAX_FOREGROUND_##level, #level); fprintf(stream, "%s", suffix_value);\
	} else {\
		fprintf(stream, "%s%s%s", prefix_value, #level, suffix_value);\
	}
#else

#define LOGAX_INITIALIZE_HCONSOLE()

#ifndef LOGAX_NO_COLORING
#define LOGAX_DELEGATE_FPRINT_STR(foreground, text) if (is_colored) { fprintf(stream, "%s%s%s", foreground, text, LOGAX_RESET_TERMINAL); } else { fprintf(stream, "%s", text); }
#define LOGAX_DELEGATE_FPRINT_SIZE_T(foreground, text) if (is_colored) { fprintf(stream, "%s%zu%s", foreground, text, LOGAX_RESET_TERMINAL); } else { fprintf(stream, "%zu", text); }
#else
#define LOGAX_DELEGATE_FPRINT_STR(foreground, text) fprintf(stream, "%s", text);
#define LOGAX_DELEGATE_FPRINT_SIZE_T(foreground, text) fprintf(stream, "%zu", text);
#endif

#ifndef LOGAX_NO_COLORING
/**
*/
#define LOGAX_WRITE_COLOR_CODE(color) if (is_colored) { fprintf(stream, "%s", color); }
#else
#define LOGAX_WRITE_COLOR_CODE(color)
#endif

/**
*/
#define LOGAX_WRITE_LEVEL_COLOR__INTERNALL__(prefix_value, level, suffix_value)\
    if (is_colored) { LOGAX_DELEGATE_FPRINT_STR(LOGAX_FOREGROUND_##level, #level); fprintf(stream, "%s", suffix_value); }\
    else fprintf(stream, "%s%s%s", prefix_value, #level, suffix_value);
#endif

/**
*/
static void logax_write_text_format_to_stream_final__internal__(FILE *stream, int flags, const char *file_path, const size_t line_number, const char *function_name, const char *fmt, va_list va_args) {
    if (flags & LOGAX_OPTION_QUITE) return;
	LOGAX_INITIALIZE_HCONSOLE();
#ifndef LOGAX_NO_COLORING
    unsigned is_colored = (flags & LOGAX_OPTION_COLORED || (flags & LOGAX_OPTION_ALL));
#else
    unsigned is_colored = 0;
#endif
	unsigned print_comma = 0;
	unsigned has_any_level = (flags & LOGAX_LEVEL_TRACE) || (flags & LOGAX_LEVEL_DEBUG) || (flags & LOGAX_LEVEL_INFO) || 
		(flags & LOGAX_LEVEL_WARN) || (flags & LOGAX_LEVEL_ERROR) || (flags & LOGAX_LEVEL_FATAL);
    /* date and time */
#ifndef LOGAX_NO_TIME
    time_t time_raw = time(LOGAX_NULL);
    struct tm *current_time = localtime(&time_raw);
    if ((flags & LOGAX_OPTION_DATE_TIME) || (flags & LOGAX_OPTION_DATE || (flags & LOGAX_OPTION_ALL))) {
        char date_buffer[16];
        date_buffer[strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", current_time)] = '\0';
		print_comma = 1;
        fprintf(stream, "%s", date_buffer);
    }
    if ((flags & LOGAX_OPTION_DATE_TIME) || (flags & LOGAX_OPTION_TIME || (flags & LOGAX_OPTION_ALL))) {
        char time_buffer[16];
        time_buffer[strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", current_time)] = '\0';
		if (print_comma) { fprintf(stream, " "); } else { print_comma = 1; }
        fprintf(stream, "%s", time_buffer);
    }
#endif
    /* logging level */
	if (print_comma && has_any_level) { fprintf(stream, " "); } else if (has_any_level) { print_comma = 1; }
    if (flags & LOGAX_LEVEL_TRACE) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("", TRACE, "");
    } else if (flags & LOGAX_LEVEL_DEBUG) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("", DEBUG, "");
    } else if (flags & LOGAX_LEVEL_INFO) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__(" ", INFO, "");
    } else if (flags & LOGAX_LEVEL_WARN) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__(" ", WARN, "");
    } else if (flags & LOGAX_LEVEL_ERROR) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("", ERROR, "");
    } else if (flags & LOGAX_LEVEL_FATAL) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("", FATAL, "");
    }
    /* file path and line number */
    if ((flags & LOGAX_OPTION_FILE_PATH) || (flags & LOGAX_OPTION_FILE_NAME_ONLY) || (flags & LOGAX_OPTION_ALL)) {
        char formatted_file_name[logax_cstr_length((char *)file_path)];
        if (flags & LOGAX_OPTION_FILE_PATH) {
            logax_replace_char((char *)file_path, formatted_file_name, '\\', '/');
        } else {
            logax_extract_name_only(file_path, formatted_file_name);
        }
		if (print_comma) { fprintf(stream, " "); } else { print_comma = 1; }
		fprintf(stream, "%s", formatted_file_name);
		if (flags & LOGAX_OPTION_LINE_NUMBER || (flags & LOGAX_OPTION_ALL)) { fprintf(stream, ":"); }
    }
    if (flags & LOGAX_OPTION_LINE_NUMBER || (flags & LOGAX_OPTION_ALL)) {
        fprintf(stream, "%zu", line_number);
		if (flags & LOGAX_OPTION_FUNCTION || (flags & LOGAX_OPTION_ALL)) { fprintf(stream, " "); }
    }
    if (flags & LOGAX_OPTION_FUNCTION || (flags & LOGAX_OPTION_ALL)) {
		if (print_comma) { fprintf(stream, " "); } else { print_comma = 1; }
        fprintf(stream, "--- [%s\t]", function_name);
    }
	if (print_comma) { fprintf(stream, " "); }
    vfprintf(stream, fmt, va_args);
    fprintf(stream, "\n");
}

/**
*/
static void logax_write_text_format_to_stream__internal__(FILE *stream, int flags, const char *file_path, const size_t line_number, const char *function_name, const char *fmt, ...) {
    va_list va_args;
    va_start(va_args, fmt);
    logax_write_text_format_to_stream_final__internal__(stream, flags, file_path, line_number, function_name, fmt, va_args);
    va_end(va_args);
}

/**
*/
#define logax_write_text_format_to_stream(stream, flags, fmt, ...) logax_write_text_format_to_stream__internal__(stream, flags, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__)

/**
*/
static void logax_write_key_value_format_to_stream_final__internal__(FILE *stream, int flags, const char *file_path, const size_t line_number, const char *function_name, const char *fmt, va_list va_args) {
    if (flags & LOGAX_OPTION_QUITE) return;
	LOGAX_INITIALIZE_HCONSOLE();
    unsigned is_colored = 0;
	unsigned print_comma = 0;
	unsigned has_any_level = (flags & LOGAX_LEVEL_TRACE) || (flags & LOGAX_LEVEL_DEBUG) || (flags & LOGAX_LEVEL_INFO) || 
		(flags & LOGAX_LEVEL_WARN) || (flags & LOGAX_LEVEL_ERROR) || (flags & LOGAX_LEVEL_FATAL);
    /* date and time */
#ifndef LOGAX_NO_TIME
    time_t time_raw = time(LOGAX_NULL);
    struct tm *current_time = localtime(&time_raw);
    if ((flags & LOGAX_OPTION_DATE_TIME) || (flags & LOGAX_OPTION_DATE || (flags & LOGAX_OPTION_ALL))) {
        char date_buffer[16];
        date_buffer[strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", current_time)] = '\0';
		print_comma = 1;
        fprintf(stream, "date=\"%s\"", date_buffer);
    }
    if ((flags & LOGAX_OPTION_DATE_TIME) || (flags & LOGAX_OPTION_TIME || (flags & LOGAX_OPTION_ALL))) {
        char time_buffer[16];
        time_buffer[strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", current_time)] = '\0';
		if (print_comma) { fprintf(stream, " "); } else { print_comma = 1; }
        fprintf(stream, "time=\"%s\"", time_buffer);
    }
#endif
    /* logging level */
	if (print_comma && has_any_level) { fprintf(stream, " "); } else if (has_any_level) { print_comma = 1; }
    if (flags & LOGAX_LEVEL_TRACE) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("level=\"", TRACE, "\"");
    } else if (flags & LOGAX_LEVEL_DEBUG) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("level=\"", DEBUG, "\"");
    } else if (flags & LOGAX_LEVEL_INFO) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("level=\"", INFO, "\"");
    } else if (flags & LOGAX_LEVEL_WARN) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("level=\"", WARN, "\"");
    } else if (flags & LOGAX_LEVEL_ERROR) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("level=\"", ERROR, "\"");
    } else if (flags & LOGAX_LEVEL_FATAL) {
        LOGAX_WRITE_LEVEL_COLOR__INTERNALL__("level=\"", FATAL, "\"");
    }
    /* file path and line number */
    if ((flags & LOGAX_OPTION_FILE_PATH) || (flags & LOGAX_OPTION_FILE_NAME_ONLY) || (flags & LOGAX_OPTION_ALL)) {
        char formatted_file_name[logax_cstr_length((char *)file_path)];
        if (flags & LOGAX_OPTION_FILE_PATH) {
            logax_replace_char((char *)file_path, formatted_file_name, '\\', '/');
        } else {
            logax_extract_name_only(file_path, formatted_file_name);
        }
		if (print_comma) { fprintf(stream, " "); } else { print_comma = 1; }
		fprintf(stream, "file=\"%s\"", formatted_file_name);
    }
    if (flags & LOGAX_OPTION_LINE_NUMBER || (flags & LOGAX_OPTION_ALL)) {
		if (print_comma) { fprintf(stream, " "); } else { print_comma = 1; }
        fprintf(stream, "line_number=%zu", line_number);
    }
    if (flags & LOGAX_OPTION_FUNCTION || (flags & LOGAX_OPTION_ALL)) {
		if (print_comma) { fprintf(stream, " "); } else { print_comma = 1; }
        fprintf(stream, "function=\"%s\"", function_name);
    }
	if (print_comma) { fprintf(stream, " "); }
    fprintf(stream, "message=\"");
    vfprintf(stream, fmt, va_args);
    fprintf(stream, "\"\n");
}

/**
*/
static void logax_write_key_value_format_to_stream__internal__(FILE *stream, int flags, const char *file_path, const size_t line_number, const char *function_name, const char *fmt, ...) {
    va_list va_args;
    va_start(va_args, fmt);
    logax_write_key_value_format_to_stream_final__internal__(stream, flags, file_path, line_number, function_name, fmt, va_args);
    va_end(va_args);
}

/**
*/
#define logax_write_key_value_format_to_stream(stream, flags, fmt, ...) logax_write_key_value_format_to_stream__internal__(stream, flags, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__)

/**
*/
#define LOGAX_INTERNAL_WRITE_JSON_STR(key, value)\
	LOGAX_DELEGATE_FPRINT_STR(LOGAX_FOREGROUND_DEBUG, "\"" key "\""); fprintf(stream, ":");\
	LOGAX_WRITE_COLOR_CODE(LOGAX_FOREGROUND_TRACE); fprintf(stream, "\"%s\"", value); if (is_colored) { LOGAX_RESET_TERMINAL_ATTR(); }

/**
*/
#define LOGAX_INTERNAL_WRITE_JSON_SIZE_T(key, value)\
	LOGAX_DELEGATE_FPRINT_STR(LOGAX_FOREGROUND_DEBUG, "\"" key "\""); fprintf(stream, ":");\
	LOGAX_DELEGATE_FPRINT_SIZE_T(LOGAX_FOREGROUND_TRACE, value);

/**
*/
static void logax_write_json_format_to_stream_final__internal__(FILE *stream, int flags, const char *file_path, const size_t line_number, const char *function_name, const char *fmt, va_list va_args) {
    if (flags & LOGAX_OPTION_QUITE) return;
	LOGAX_INITIALIZE_HCONSOLE();
#ifndef LOGAX_NO_COLORING
    unsigned is_colored = (flags & LOGAX_OPTION_COLORED || (flags & LOGAX_OPTION_ALL));
#else
    unsigned is_colored = 0;
#endif
	unsigned print_comma = 0;
	unsigned has_any_level = (flags & LOGAX_LEVEL_TRACE) || (flags & LOGAX_LEVEL_DEBUG) || (flags & LOGAX_LEVEL_INFO) || 
		(flags & LOGAX_LEVEL_WARN) || (flags & LOGAX_LEVEL_ERROR) || (flags & LOGAX_LEVEL_FATAL);
    /* date and time */
    fprintf(stream, "{");
#ifndef LOGAX_NO_TIME
    time_t time_raw = time(LOGAX_NULL);
    struct tm *current_time = localtime(&time_raw);
    if ((flags & LOGAX_OPTION_DATE_TIME) || (flags & LOGAX_OPTION_DATE || (flags & LOGAX_OPTION_ALL))) {
        char date_buffer[16];
          date_buffer[strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", current_time)] = '\0';

		print_comma = 1;
		LOGAX_INTERNAL_WRITE_JSON_STR("date", date_buffer);
    }
    if ((flags & LOGAX_OPTION_DATE_TIME) || (flags & LOGAX_OPTION_TIME) || (flags & LOGAX_OPTION_ALL)) {
        char time_buffer[16];
          time_buffer[strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", current_time)] = '\0';
        if (print_comma) { fprintf(stream, ","); } else { print_comma = 1; }
		LOGAX_INTERNAL_WRITE_JSON_STR("time", time_buffer);
    }
#endif
    /* logging level */
	if (print_comma && has_any_level) { fprintf(stream, ","); } else if (has_any_level) { print_comma = 1; }
    if (flags & LOGAX_LEVEL_TRACE) {
		LOGAX_INTERNAL_WRITE_JSON_STR("level", "TRACE");
    } else if (flags & LOGAX_LEVEL_DEBUG) {
		LOGAX_INTERNAL_WRITE_JSON_STR("level", "DEBUG");
    } else if (flags & LOGAX_LEVEL_INFO) {
		LOGAX_INTERNAL_WRITE_JSON_STR("level", "INFO");
    } else if (flags & LOGAX_LEVEL_WARN) {
		LOGAX_INTERNAL_WRITE_JSON_STR("level", "WARN");
    } else if (flags & LOGAX_LEVEL_ERROR) {
		LOGAX_INTERNAL_WRITE_JSON_STR("level", "ERROR");
    } else if (flags & LOGAX_LEVEL_FATAL) {
		LOGAX_INTERNAL_WRITE_JSON_STR("level", "FATAL");
    }
    /* file path and line number */
    if ((flags & LOGAX_OPTION_FILE_PATH) || (flags & LOGAX_OPTION_FILE_NAME_ONLY) || (flags & LOGAX_OPTION_ALL)) {
        char formatted_file_name[logax_cstr_length((char *)file_path)];
        if (flags & LOGAX_OPTION_FILE_PATH) {
            logax_replace_char((char *)file_path, formatted_file_name, '\\', '/');
        } else {
            logax_extract_name_only(file_path, formatted_file_name);
        }
		if (print_comma) { fprintf(stream, ","); } else { print_comma = 1; }
		LOGAX_INTERNAL_WRITE_JSON_STR("file", formatted_file_name);
    }
    if (flags & LOGAX_OPTION_LINE_NUMBER || (flags & LOGAX_OPTION_ALL)) {
		if (print_comma) { fprintf(stream, ","); } else { print_comma = 1; }
		LOGAX_INTERNAL_WRITE_JSON_SIZE_T("line_number", line_number);
    }
    if (flags & LOGAX_OPTION_FUNCTION || (flags & LOGAX_OPTION_ALL)) {
		if (print_comma) { fprintf(stream, ","); } else { print_comma = 1; }
		LOGAX_INTERNAL_WRITE_JSON_STR("function", function_name);
    }
	if (print_comma) { fprintf(stream, ","); }
    LOGAX_DELEGATE_FPRINT_STR(LOGAX_FOREGROUND_DEBUG, "\"message\""); fprintf(stream, ":");
    if (is_colored) {
		LOGAX_WRITE_COLOR_CODE(LOGAX_FOREGROUND_TRACE); 
		fprintf(stream, "\""); vfprintf(stream, fmt, va_args); fprintf(stream, "\"");
		LOGAX_RESET_TERMINAL_ATTR();
	} else {
		fprintf(stream, "\""); vfprintf(stream, fmt, va_args); fprintf(stream, "\"");
	}
    fprintf(stream, "},\n");
}

/**
*/
static void logax_write_json_format_to_stream__internal__(FILE *stream, int flags, const char *file_path, const size_t line_number, const char *function_name, const char *fmt, ...) {
    va_list va_args;
    va_start(va_args, fmt);
    logax_write_json_format_to_stream_final__internal__(stream, flags, file_path, line_number, function_name, fmt, va_args);
    va_end(va_args);
}

/**
*/
#define logax_write_json_format_to_stream(stream, flags, fmt, ...) logax_write_json_format_to_stream__internal__(stream, flags, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__)
#else
#define logax_write_text_format_to_stream(stream, flags, fmt, ...)
#define logax_write_key_value_format_to_stream(stream, flags, fmt, ...)
#define logax_write_json_format_to_stream(stream, flags, fmt, ...)

#endif

#if !defined(LOGAX_NO_OUTPUT_STREAM) && !defined(LOGAX_LOGGER_NO_OUTPUT_STREAM)
/**
    
*/
static void logax_logger_write(LogaxLogger *logax_logger, int level, const char *file_path, const size_t line_number, const char *function_name, const char *fmt, ...) {
    logax_logger->flags |= level;
    va_list args;

    va_start(args, fmt);
    if (logax_logger->flags & LOGAX_FORMATTER_JSON) {
        logax_write_json_format_to_stream_final__internal__(logax_logger->output_stream, logax_logger->flags, file_path, line_number, function_name, fmt, args);
    } else if (logax_logger->flags & LOGAX_FORMATTER_KEY_VALUE) {
        logax_write_key_value_format_to_stream_final__internal__(logax_logger->output_stream, logax_logger->flags, file_path, line_number, function_name, fmt, args);
    } else {
        logax_write_text_format_to_stream_final__internal__(logax_logger->output_stream, logax_logger->flags, file_path, line_number, function_name, fmt, args);
    }
    va_end(args);
    logax_logger->flags &= ~level;
}
#else
#define logax_logger_write(logax_logger, level, file_path, line_number, function_name, fmt, ...)
#endif

#ifndef LOGAX_LOGGER_NO_CALLBACK
/**
    
*//* TODO: Refractor to a function */
#ifndef LOGAX_NO_TIME
    #define logax_logger_report_to_callback(logax_logger, level, fmt, ...) {\
            int index = 0;\
            char time_buffer__logax_tmp_var__[16];\
            char date_buffer__logax_tmp_var__[16];\
            time_t time_raw__logax_tmp_var__ = time(LOGAX_NULL);\
            struct tm *current_time__logax_tmp_var__ = localtime(&time_raw__logax_tmp_var__);\
            date_buffer__logax_tmp_var__[strftime(date_buffer__logax_tmp_var__, sizeof(date_buffer__logax_tmp_var__), "%Y-%m-%d", current_time__logax_tmp_var__)] = '\0';\
            time_buffer__logax_tmp_var__[strftime(time_buffer__logax_tmp_var__, sizeof(time_buffer__logax_tmp_var__), "%H:%M:%S", current_time__logax_tmp_var__)] = '\0';\
            for (; index < LOGAX_MAX_CALLBACKS; index++) {\
                logax_callback callback = (logax_logger)->callbacks[index];\
                if (callback != LOGAX_NULL) {\
                    callback(date_buffer__logax_tmp_var__, time_buffer__logax_tmp_var__, level, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
                }\
            }\
        }
#else
    #define logax_logger_report_to_callback(logax_logger, level, fmt, ...) {\
            int index = 0;\
            for (; index < LOGAX_MAX_CALLBACKS; index++) {\
                logax_callback callback = (logax_logger)->callbacks[index];\
                if (callback != LOGAX_NULL) {\
                    callback(LOGAX_NULL, LOGAX_NULL, level, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
                }\
            }\
        }
#endif
#else
#define logax_logger_report_to_callback(logax_logger, level, fmt, ...)
#endif

/**
    
*/
#define logax_logger_trace(logax_logger, fmt, ...) logax_logger_write(logax_logger, LOGAX_LEVEL_TRACE, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
    logax_logger_report_to_callback(logax_logger, LOGAX_LEVEL_TRACE, fmt, __VA_ARGS__)

/**
    
*/
#define logax_logger_debug(logax_logger, fmt, ...) logax_logger_write(logax_logger, LOGAX_LEVEL_DEBUG, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
    logax_logger_report_to_callback(logax_logger, LOGAX_LEVEL_DEBUG, fmt, __VA_ARGS__)

/**
    
*/
#define logax_logger_info(logax_logger, fmt, ...) logax_logger_write(logax_logger, LOGAX_LEVEL_INFO, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
    logax_logger_report_to_callback(logax_logger, LOGAX_LEVEL_INFO, fmt, __VA_ARGS__)

/**
    
*/
#define logax_logger_warn(logax_logger, fmt, ...) logax_logger_write(logax_logger, LOGAX_LEVEL_WARN, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
    logax_logger_report_to_callback(logax_logger, LOGAX_LEVEL_WARN, fmt, __VA_ARGS__)

/**
    
*/
#define logax_logger_error(logax_logger, fmt, ...) logax_logger_write(logax_logger, LOGAX_LEVEL_ERROR, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
    logax_logger_report_to_callback(logax_logger, LOGAX_LEVEL_ERROR, fmt, __VA_ARGS__)

/**
    
*/
#define logax_logger_fatal(logax_logger, fmt, ...) logax_logger_write(logax_logger, LOGAX_LEVEL_FATAL, __FILE__, __LINE__, __LOGAX_FUNCTION__, fmt, __VA_ARGS__);\
    logax_logger_report_to_callback(logax_logger, LOGAX_LEVEL_FATAL, fmt, __VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif