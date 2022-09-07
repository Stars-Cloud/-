#define NAPI_RETVAL_NOTHING

#define GET_AND_THROW_LAST_ERROR(env)
    do{
        const napi_extended_error_info *error_info;
        napi_get_last_error_info((env),&error_info);
        bool is_pending;
        napi_is_exception_pending((env),&is_pending);
        /*If an exception is already pending, don`t rethrow it*/
        if(!is_pending){
            const char* error_message = error_info->error_message != NULL?
            error_info->error_message:
            "empty error message";
            napi_throw_error((env),NULL,error_message);
        }
    }while(0)

#define NAPI_ASSERT_BASE(env,assertion, message,ret_val)
    do{
        if(!(assertion)){
            napi_throw_error(
            (env),
            NULL,
            "assertion (" #assertion ") failed:" message);
            return ret_val
        }
    }while(0)

#define NAPI_ASSERT(env,assertion,message)
    NAPI_ASSERT_BASE(env,assertion,message,NULL)

#define NAPI_ASSERT_RETURN_VOID(env,assertion,message)
    NAPI_ASSERT_BASE(env,assertion,message,NAPI_RETVAL_NOTHING)

#define NAPI_CALL_BASE(env,the_call,ret_val)
    do{
        if((the_call) != napi_ok){
            GET_AND_THROW_LAST_ERROR((env));
            return ret_val;
        }
    }while(0)


#define NAPI_CALL_BASE(env,the_call)
    NAPI_CALL_BASE(env,the_call,NULL)

#define NAPI_CALL_NAPI_ASSERT_RETURN_VOID(env,the_call)
    NAPI_CALL_BASE(env,the_call,NAPI_RETVAL_NOTHING)

#define DECLARE_NAPI_PROPERTY(name,func)
    {(name),0,(func),0,0,0,napi_default,0}

#define DECLARE_NAPI_GETTER(name,func)
    {(name),0,0,(func),0,0,napi_default,0}