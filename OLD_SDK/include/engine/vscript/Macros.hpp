//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#pragma region macros
#define AssertMsg(_exp, _msg) ((void)0)

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_0
#define FUNC_TEMPLATE_ARG_PARAMS_0
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_0
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_0
#define FUNC_ARG_MEMBERS_0
#define FUNC_ARG_FORMAL_PARAMS_0
#define FUNC_PROXY_ARG_FORMAL_PARAMS_0
#define FUNC_CALL_ARGS_INIT_0
#define FUNC_SOLO_CALL_ARGS_INIT_0
#define FUNC_CALL_MEMBER_ARGS_0
#define FUNC_CALL_ARGS_0
#define FUNC_CALL_DATA_ARGS_0(_var)
#define FUNC_FUNCTOR_CALL_ARGS_0
#define FUNC_TEMPLATE_FUNC_PARAMS_0
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_0
#define FUNC_VALIDATION_STRING_0 Q_snprintf(pString, nBufLen, "method( void )");

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_1 typename ARG_TYPE_1
#define FUNC_TEMPLATE_ARG_PARAMS_1 , typename ARG_TYPE_1
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_1 , ARG_TYPE_1
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_1 ARG_TYPE_1
#define FUNC_ARG_MEMBERS_1 ARG_TYPE_1 m_arg1
#define FUNC_ARG_FORMAL_PARAMS_1 , const ARG_TYPE_1& arg1
#define FUNC_PROXY_ARG_FORMAL_PARAMS_1 const ARG_TYPE_1& arg1
#define FUNC_CALL_ARGS_INIT_1 , m_arg1(arg1)
#define FUNC_SOLO_CALL_ARGS_INIT_1			: m_arg1( arg1 )
#define FUNC_CALL_MEMBER_ARGS_1 m_arg1
#define FUNC_CALL_ARGS_1 arg1
#define FUNC_CALL_DATA_ARGS_1(_var) _var->m_arg1
#define FUNC_FUNCTOR_CALL_ARGS_1 , arg1
#define FUNC_TEMPLATE_FUNC_PARAMS_1 , typename FUNC_ARG_TYPE_1
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_1 FUNC_ARG_TYPE_1
#define FUNC_VALIDATION_STRING_1 Q_snprintf(pString, nBufLen, "method( %s )", typeid(ARG_TYPE_1).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_2 typename ARG_TYPE_1, typename ARG_TYPE_2
#define FUNC_TEMPLATE_ARG_PARAMS_2 , typename ARG_TYPE_1, typename ARG_TYPE_2
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_2 , ARG_TYPE_1, ARG_TYPE_2
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_2 ARG_TYPE_1, ARG_TYPE_2
#define FUNC_ARG_MEMBERS_2 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2
#define FUNC_ARG_FORMAL_PARAMS_2 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2
#define FUNC_PROXY_ARG_FORMAL_PARAMS_2 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2
#define FUNC_CALL_ARGS_INIT_2 , m_arg1(arg1), m_arg2(arg2)
#define FUNC_SOLO_CALL_ARGS_INIT_2			: m_arg1( arg1 ), m_arg2( arg2 )
#define FUNC_CALL_MEMBER_ARGS_2 m_arg1, m_arg2
#define FUNC_CALL_ARGS_2 arg1, arg2
#define FUNC_CALL_DATA_ARGS_2(_var) _var->m_arg1, _var->m_arg2
#define FUNC_FUNCTOR_CALL_ARGS_2 , arg1, arg2
#define FUNC_TEMPLATE_FUNC_PARAMS_2 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_2 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2
#define FUNC_VALIDATION_STRING_2 Q_snprintf(pString, nBufLen, "method( %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_3 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3
#define FUNC_TEMPLATE_ARG_PARAMS_3 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_3 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_3 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3
#define FUNC_ARG_MEMBERS_3 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2;     \
    ARG_TYPE_3 m_arg3
#define FUNC_ARG_FORMAL_PARAMS_3 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3
#define FUNC_PROXY_ARG_FORMAL_PARAMS_3 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3
#define FUNC_CALL_ARGS_INIT_3 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3)
#define FUNC_SOLO_CALL_ARGS_INIT_3			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 )
#define FUNC_CALL_MEMBER_ARGS_3 m_arg1, m_arg2, m_arg3
#define FUNC_CALL_ARGS_3 arg1, arg2, arg3
#define FUNC_CALL_DATA_ARGS_3(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3
#define FUNC_FUNCTOR_CALL_ARGS_3 , arg1, arg2, arg3
#define FUNC_TEMPLATE_FUNC_PARAMS_3 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_3 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3
#define FUNC_VALIDATION_STRING_3 Q_snprintf(pString, nBufLen, "method( %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_4 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4
#define FUNC_TEMPLATE_ARG_PARAMS_4 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_4 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_4 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4
#define FUNC_ARG_MEMBERS_4 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2;     \
    ARG_TYPE_3 m_arg3;     \
    ARG_TYPE_4 m_arg4
#define FUNC_ARG_FORMAL_PARAMS_4 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4
#define FUNC_PROXY_ARG_FORMAL_PARAMS_4 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4
#define FUNC_CALL_ARGS_INIT_4 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4)
#define FUNC_SOLO_CALL_ARGS_INIT_4			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 )
#define FUNC_CALL_MEMBER_ARGS_4 m_arg1, m_arg2, m_arg3, m_arg4
#define FUNC_CALL_ARGS_4 arg1, arg2, arg3, arg4
#define FUNC_CALL_DATA_ARGS_4(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4
#define FUNC_FUNCTOR_CALL_ARGS_4 , arg1, arg2, arg3, arg4
#define FUNC_TEMPLATE_FUNC_PARAMS_4 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_4 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4
#define FUNC_VALIDATION_STRING_4 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_5 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5
#define FUNC_TEMPLATE_ARG_PARAMS_5 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_5 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_5 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5
#define FUNC_ARG_MEMBERS_5 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2;     \
    ARG_TYPE_3 m_arg3;     \
    ARG_TYPE_4 m_arg4;     \
    ARG_TYPE_5 m_arg5
#define FUNC_ARG_FORMAL_PARAMS_5 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5
#define FUNC_PROXY_ARG_FORMAL_PARAMS_5 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5
#define FUNC_CALL_ARGS_INIT_5 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5)
#define FUNC_SOLO_CALL_ARGS_INIT_5			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 )
#define FUNC_CALL_MEMBER_ARGS_5 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5
#define FUNC_CALL_ARGS_5 arg1, arg2, arg3, arg4, arg5
#define FUNC_CALL_DATA_ARGS_5(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5
#define FUNC_FUNCTOR_CALL_ARGS_5 , arg1, arg2, arg3, arg4, arg5
#define FUNC_TEMPLATE_FUNC_PARAMS_5 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_5 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5
#define FUNC_VALIDATION_STRING_5 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_6 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6
#define FUNC_TEMPLATE_ARG_PARAMS_6 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_6 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_6 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6
#define FUNC_ARG_MEMBERS_6 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2;     \
    ARG_TYPE_3 m_arg3;     \
    ARG_TYPE_4 m_arg4;     \
    ARG_TYPE_5 m_arg5;     \
    ARG_TYPE_6 m_arg6
#define FUNC_ARG_FORMAL_PARAMS_6 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6
#define FUNC_PROXY_ARG_FORMAL_PARAMS_6 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6
#define FUNC_CALL_ARGS_INIT_6 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6)
#define FUNC_SOLO_CALL_ARGS_INIT_6			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 )
#define FUNC_CALL_MEMBER_ARGS_6 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6
#define FUNC_CALL_ARGS_6 arg1, arg2, arg3, arg4, arg5, arg6
#define FUNC_CALL_DATA_ARGS_6(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6
#define FUNC_FUNCTOR_CALL_ARGS_6 , arg1, arg2, arg3, arg4, arg5, arg6
#define FUNC_TEMPLATE_FUNC_PARAMS_6 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_6 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6
#define FUNC_VALIDATION_STRING_6 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_7 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7
#define FUNC_TEMPLATE_ARG_PARAMS_7 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_7 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_7 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7
#define FUNC_ARG_MEMBERS_7 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2;     \
    ARG_TYPE_3 m_arg3;     \
    ARG_TYPE_4 m_arg4;     \
    ARG_TYPE_5 m_arg5;     \
    ARG_TYPE_6 m_arg6;     \
    ARG_TYPE_7 m_arg7;
#define FUNC_ARG_FORMAL_PARAMS_7 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7
#define FUNC_PROXY_ARG_FORMAL_PARAMS_7 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7
#define FUNC_CALL_ARGS_INIT_7 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7)
#define FUNC_SOLO_CALL_ARGS_INIT_7			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 )
#define FUNC_CALL_MEMBER_ARGS_7 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7
#define FUNC_CALL_ARGS_7 arg1, arg2, arg3, arg4, arg5, arg6, arg7
#define FUNC_CALL_DATA_ARGS_7(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7
#define FUNC_FUNCTOR_CALL_ARGS_7 , arg1, arg2, arg3, arg4, arg5, arg6, arg7
#define FUNC_TEMPLATE_FUNC_PARAMS_7 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_7 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7
#define FUNC_VALIDATION_STRING_7 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_8 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8
#define FUNC_TEMPLATE_ARG_PARAMS_8 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_8 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_8 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8
#define FUNC_ARG_MEMBERS_8 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2;     \
    ARG_TYPE_3 m_arg3;     \
    ARG_TYPE_4 m_arg4;     \
    ARG_TYPE_5 m_arg5;     \
    ARG_TYPE_6 m_arg6;     \
    ARG_TYPE_7 m_arg7;     \
    ARG_TYPE_8 m_arg8;
#define FUNC_ARG_FORMAL_PARAMS_8 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8
#define FUNC_PROXY_ARG_FORMAL_PARAMS_8 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8
#define FUNC_CALL_ARGS_INIT_8 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7), m_arg8(arg8)
#define FUNC_SOLO_CALL_ARGS_INIT_8			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 ), m_arg8( arg8 )
#define FUNC_CALL_MEMBER_ARGS_8 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8
#define FUNC_CALL_ARGS_8 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8
#define FUNC_CALL_DATA_ARGS_8(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7, _var->m_arg8
#define FUNC_FUNCTOR_CALL_ARGS_8 , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8
#define FUNC_TEMPLATE_FUNC_PARAMS_8 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7, typename FUNC_ARG_TYPE_8
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_8 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7, FUNC_ARG_TYPE_8
#define FUNC_VALIDATION_STRING_8 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name(), typeid(ARG_TYPE_8).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_9 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9
#define FUNC_TEMPLATE_ARG_PARAMS_9 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_9 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_9 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9
#define FUNC_ARG_MEMBERS_9 \
    ARG_TYPE_1 m_arg1;     \
    ARG_TYPE_2 m_arg2;     \
    ARG_TYPE_3 m_arg3;     \
    ARG_TYPE_4 m_arg4;     \
    ARG_TYPE_5 m_arg5;     \
    ARG_TYPE_6 m_arg6;     \
    ARG_TYPE_7 m_arg7;     \
    ARG_TYPE_8 m_arg8;     \
    ARG_TYPE_9 m_arg9;
#define FUNC_ARG_FORMAL_PARAMS_9 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9
#define FUNC_PROXY_ARG_FORMAL_PARAMS_9 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9
#define FUNC_CALL_ARGS_INIT_9 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7), m_arg8(arg8), m_arg9(arg9)
#define FUNC_SOLO_CALL_ARGS_INIT_9			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 ), m_arg8( arg8 ), m_arg9( arg9 )
#define FUNC_CALL_MEMBER_ARGS_9 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9
#define FUNC_CALL_ARGS_9 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9
#define FUNC_CALL_DATA_ARGS_9(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7, _var->m_arg8, _var->m_arg9
#define FUNC_FUNCTOR_CALL_ARGS_9 , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9
#define FUNC_TEMPLATE_FUNC_PARAMS_9 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7, typename FUNC_ARG_TYPE_8, typename FUNC_ARG_TYPE_9
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_9 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7, FUNC_ARG_TYPE_8, FUNC_ARG_TYPE_9
#define FUNC_VALIDATION_STRING_9 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name(), typeid(ARG_TYPE_8).name(), typeid(ARG_TYPE_9).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_10 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10
#define FUNC_TEMPLATE_ARG_PARAMS_10 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_10 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_10 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10
#define FUNC_ARG_MEMBERS_10 \
    ARG_TYPE_1 m_arg1;      \
    ARG_TYPE_2 m_arg2;      \
    ARG_TYPE_3 m_arg3;      \
    ARG_TYPE_4 m_arg4;      \
    ARG_TYPE_5 m_arg5;      \
    ARG_TYPE_6 m_arg6;      \
    ARG_TYPE_7 m_arg7;      \
    ARG_TYPE_8 m_arg8;      \
    ARG_TYPE_9 m_arg9;      \
    ARG_TYPE_10 m_arg10;
#define FUNC_ARG_FORMAL_PARAMS_10 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10
#define FUNC_PROXY_ARG_FORMAL_PARAMS_10 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10
#define FUNC_CALL_ARGS_INIT_10 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7), m_arg8(arg8), m_arg9(arg9), m_arg10(arg10)
#define FUNC_SOLO_CALL_ARGS_INIT_10			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 ), m_arg8( arg8 ), m_arg9( arg9 ), m_arg10( arg10 )
#define FUNC_CALL_MEMBER_ARGS_10 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9, m_arg10
#define FUNC_CALL_ARGS_10 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10
#define FUNC_CALL_DATA_ARGS_10(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7, _var->m_arg8, _var->m_arg9, _var->m_arg10
#define FUNC_FUNCTOR_CALL_ARGS_10 , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10
#define FUNC_TEMPLATE_FUNC_PARAMS_10 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7, typename FUNC_ARG_TYPE_8, typename FUNC_ARG_TYPE_9, typename FUNC_ARG_TYPE_10
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_10 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7, FUNC_ARG_TYPE_8, FUNC_ARG_TYPE_9, FUNC_ARG_TYPE_10
#define FUNC_VALIDATION_STRING_10 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name(), typeid(ARG_TYPE_8).name(), typeid(ARG_TYPE_9).name(), typeid(ARG_TYPE_10).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_11 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11
#define FUNC_TEMPLATE_ARG_PARAMS_11 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_11 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_11 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11
#define FUNC_ARG_MEMBERS_11 \
    ARG_TYPE_1 m_arg1;      \
    ARG_TYPE_2 m_arg2;      \
    ARG_TYPE_3 m_arg3;      \
    ARG_TYPE_4 m_arg4;      \
    ARG_TYPE_5 m_arg5;      \
    ARG_TYPE_6 m_arg6;      \
    ARG_TYPE_7 m_arg7;      \
    ARG_TYPE_8 m_arg8;      \
    ARG_TYPE_9 m_arg9;      \
    ARG_TYPE_10 m_arg10;    \
    ARG_TYPE_11 m_arg11
#define FUNC_ARG_FORMAL_PARAMS_11 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11
#define FUNC_PROXY_ARG_FORMAL_PARAMS_11 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11
#define FUNC_CALL_ARGS_INIT_11 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7), m_arg8(arg8), m_arg9(arg9), m_arg10(arg10), m_arg11(arg11)
#define FUNC_SOLO_CALL_ARGS_INIT_11			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 ), m_arg8( arg8 ), m_arg9( arg9 ), m_arg10( arg10 ), m_arg11( arg11 )
#define FUNC_CALL_MEMBER_ARGS_11 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9, m_arg10, m_arg11
#define FUNC_CALL_ARGS_11 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11
#define FUNC_CALL_DATA_ARGS_11(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7, _var->m_arg8, _var->m_arg9, _var->m_arg10, _var->m_arg11
#define FUNC_FUNCTOR_CALL_ARGS_11 , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11
#define FUNC_TEMPLATE_FUNC_PARAMS_11 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7, typename FUNC_ARG_TYPE_8, typename FUNC_ARG_TYPE_9, typename FUNC_ARG_TYPE_10, typename FUNC_ARG_TYPE_11
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_11 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7, FUNC_ARG_TYPE_8, FUNC_ARG_TYPE_9, FUNC_ARG_TYPE_10, FUNC_ARG_TYPE_11
#define FUNC_VALIDATION_STRING_11 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name(), typeid(ARG_TYPE_8).name(), typeid(ARG_TYPE_9).name(), typeid(ARG_TYPE_10).name(), typeid(ARG_TYPE_11).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_12 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12
#define FUNC_TEMPLATE_ARG_PARAMS_12 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_12 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11, ARG_TYPE_12
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_12 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11, ARG_TYPE_12
#define FUNC_ARG_MEMBERS_12 \
    ARG_TYPE_1 m_arg1;      \
    ARG_TYPE_2 m_arg2;      \
    ARG_TYPE_3 m_arg3;      \
    ARG_TYPE_4 m_arg4;      \
    ARG_TYPE_5 m_arg5;      \
    ARG_TYPE_6 m_arg6;      \
    ARG_TYPE_7 m_arg7;      \
    ARG_TYPE_8 m_arg8;      \
    ARG_TYPE_9 m_arg9;      \
    ARG_TYPE_10 m_arg10;    \
    ARG_TYPE_11 m_arg11;    \
    ARG_TYPE_12 m_arg12
#define FUNC_ARG_FORMAL_PARAMS_12 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11, const ARG_TYPE_12 &arg12
#define FUNC_PROXY_ARG_FORMAL_PARAMS_12 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11, const ARG_TYPE_12 &arg12
#define FUNC_CALL_ARGS_INIT_12 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7), m_arg8(arg8), m_arg9(arg9), m_arg10(arg10), m_arg11(arg11), m_arg12(arg12)
#define FUNC_SOLO_CALL_ARGS_INIT_12			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 ), m_arg8( arg8 ), m_arg9( arg9 ), m_arg10( arg10 ), m_arg11( arg11 ), m_arg12( arg12 )
#define FUNC_CALL_MEMBER_ARGS_12 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9, m_arg10, m_arg11, m_arg12
#define FUNC_CALL_ARGS_12 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12
#define FUNC_CALL_DATA_ARGS_12(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7, _var->m_arg8, _var->m_arg9, _var->m_arg10, _var->m_arg11, _var->m_arg12
#define FUNC_FUNCTOR_CALL_ARGS_12 , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12
#define FUNC_TEMPLATE_FUNC_PARAMS_12 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7, typename FUNC_ARG_TYPE_8, typename FUNC_ARG_TYPE_9, typename FUNC_ARG_TYPE_10, typename FUNC_ARG_TYPE_11, typename FUNC_ARG_TYPE_12
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_12 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7, FUNC_ARG_TYPE_8, FUNC_ARG_TYPE_9, FUNC_ARG_TYPE_10, FUNC_ARG_TYPE_11, FUNC_ARG_TYPE_12
#define FUNC_VALIDATION_STRING_12 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name(), typeid(ARG_TYPE_8).name(), typeid(ARG_TYPE_9).name(), typeid(ARG_TYPE_10).name(), typeid(ARG_TYPE_11).name(), typeid(ARG_TYPE_12).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_13 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12, typename ARG_TYPE_13
#define FUNC_TEMPLATE_ARG_PARAMS_13 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12, typename ARG_TYPE_13
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_13 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11, ARG_TYPE_12, ARG_TYPE_13
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_13 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11, ARG_TYPE_12, ARG_TYPE_13
#define FUNC_ARG_MEMBERS_13 \
    ARG_TYPE_1 m_arg1;      \
    ARG_TYPE_2 m_arg2;      \
    ARG_TYPE_3 m_arg3;      \
    ARG_TYPE_4 m_arg4;      \
    ARG_TYPE_5 m_arg5;      \
    ARG_TYPE_6 m_arg6;      \
    ARG_TYPE_7 m_arg7;      \
    ARG_TYPE_8 m_arg8;      \
    ARG_TYPE_9 m_arg9;      \
    ARG_TYPE_10 m_arg10;    \
    ARG_TYPE_11 m_arg11;    \
    ARG_TYPE_12 m_arg12;    \
    ARG_TYPE_13 m_arg13
#define FUNC_ARG_FORMAL_PARAMS_13 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11, const ARG_TYPE_12 &arg12, const ARG_TYPE_13 &arg13
#define FUNC_PROXY_ARG_FORMAL_PARAMS_13 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11, const ARG_TYPE_12 &arg12, const ARG_TYPE_13 &arg13
#define FUNC_CALL_ARGS_INIT_13 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7), m_arg8(arg8), m_arg9(arg9), m_arg10(arg10), m_arg11(arg11), m_arg12(arg12), m_arg13(arg13)
#define FUNC_SOLO_CALL_ARGS_INIT_13			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 ), m_arg8( arg8 ), m_arg9( arg9 ), m_arg10( arg10 ), m_arg11( arg11 ), m_arg12( arg12 ), m_arg13( arg13 )
#define FUNC_CALL_MEMBER_ARGS_13 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9, m_arg10, m_arg11, m_arg12, m_arg13
#define FUNC_CALL_ARGS_13 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13
#define FUNC_CALL_DATA_ARGS_13(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7, _var->m_arg8, _var->m_arg9, _var->m_arg10, _var->m_arg11, _var->m_arg12, _var->m_arg13
#define FUNC_FUNCTOR_CALL_ARGS_13 , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13
#define FUNC_TEMPLATE_FUNC_PARAMS_13 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7, typename FUNC_ARG_TYPE_8, typename FUNC_ARG_TYPE_9, typename FUNC_ARG_TYPE_10, typename FUNC_ARG_TYPE_11, typename FUNC_ARG_TYPE_12, typename FUNC_ARG_TYPE_13
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_13 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7, FUNC_ARG_TYPE_8, FUNC_ARG_TYPE_9, FUNC_ARG_TYPE_10, FUNC_ARG_TYPE_11, FUNC_ARG_TYPE_12, FUNC_ARG_TYPE_13
#define FUNC_VALIDATION_STRING_13 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name(), typeid(ARG_TYPE_8).name(), typeid(ARG_TYPE_9).name(), typeid(ARG_TYPE_10).name(), typeid(ARG_TYPE_11).name(), typeid(ARG_TYPE_12).name(), typeid(ARG_TYPE_13).name());

#define FUNC_SOLO_TEMPLATE_ARG_PARAMS_14 typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12, typename ARG_TYPE_13, typename ARG_TYPE_14
#define FUNC_TEMPLATE_ARG_PARAMS_14 , typename ARG_TYPE_1, typename ARG_TYPE_2, typename ARG_TYPE_3, typename ARG_TYPE_4, typename ARG_TYPE_5, typename ARG_TYPE_6, typename ARG_TYPE_7, typename ARG_TYPE_8, typename ARG_TYPE_9, typename ARG_TYPE_10, typename ARG_TYPE_11, typename ARG_TYPE_12, typename ARG_TYPE_13, typename ARG_TYPE_14
#define FUNC_BASE_TEMPLATE_ARG_PARAMS_14 , ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11, ARG_TYPE_12, ARG_TYPE_13, ARG_TYPE_14
#define FUNC_SOLO_BASE_TEMPLATE_ARG_PARAMS_14 ARG_TYPE_1, ARG_TYPE_2, ARG_TYPE_3, ARG_TYPE_4, ARG_TYPE_5, ARG_TYPE_6, ARG_TYPE_7, ARG_TYPE_8, ARG_TYPE_9, ARG_TYPE_10, ARG_TYPE_11, ARG_TYPE_12, ARG_TYPE_13, ARG_TYPE_14
#define FUNC_ARG_MEMBERS_14 \
    ARG_TYPE_1 m_arg1;      \
    ARG_TYPE_2 m_arg2;      \
    ARG_TYPE_3 m_arg3;      \
    ARG_TYPE_4 m_arg4;      \
    ARG_TYPE_5 m_arg5;      \
    ARG_TYPE_6 m_arg6;      \
    ARG_TYPE_7 m_arg7;      \
    ARG_TYPE_8 m_arg8;      \
    ARG_TYPE_9 m_arg9;      \
    ARG_TYPE_10 m_arg10;    \
    ARG_TYPE_11 m_arg11;    \
    ARG_TYPE_12 m_arg12;    \
    ARG_TYPE_13 m_arg13;    \
    ARG_TYPE_14 m_arg14
#define FUNC_ARG_FORMAL_PARAMS_14 , const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11, const ARG_TYPE_12 &arg12, const ARG_TYPE_13 &arg13, const ARG_TYPE_14 &arg14
#define FUNC_PROXY_ARG_FORMAL_PARAMS_14 const ARG_TYPE_1 &arg1, const ARG_TYPE_2 &arg2, const ARG_TYPE_3 &arg3, const ARG_TYPE_4 &arg4, const ARG_TYPE_5 &arg5, const ARG_TYPE_6 &arg6, const ARG_TYPE_7 &arg7, const ARG_TYPE_8 &arg8, const ARG_TYPE_9 &arg9, const ARG_TYPE_10 &arg10, const ARG_TYPE_11 &arg11, const ARG_TYPE_12 &arg12, const ARG_TYPE_13 &arg13, const ARG_TYPE_14 &arg14
#define FUNC_CALL_ARGS_INIT_14 , m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7), m_arg8(arg8), m_arg9(arg9), m_arg10(arg10), m_arg11(arg11), m_arg12(arg12), m_arg13(arg13), m_arg14(arg14)
#define FUNC_SOLO_CALL_ARGS_INIT_14			: m_arg1( arg1 ), m_arg2( arg2 ), m_arg3( arg3 ), m_arg4( arg4 ), m_arg5( arg5 ), m_arg6( arg6 ), m_arg7( arg7 ), m_arg8( arg8 ), m_arg9( arg9 ), m_arg10( arg10 ), m_arg11( arg11 ), m_arg12( arg12 ), m_arg13( arg13 ), m_arg14( arg14 )
#define FUNC_CALL_MEMBER_ARGS_14 m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9, m_arg10, m_arg11, m_arg12, m_arg13, m_arg14
#define FUNC_CALL_ARGS_14 arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14
#define FUNC_CALL_DATA_ARGS_14(_var) _var->m_arg1, _var->m_arg2, _var->m_arg3, _var->m_arg4, _var->m_arg5, _var->m_arg6, _var->m_arg7, _var->m_arg8, _var->m_arg9, _var->m_arg10, _var->m_arg11, _var->m_arg12, _var->m_arg13, _var->m_arg14
#define FUNC_FUNCTOR_CALL_ARGS_14 , arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14
#define FUNC_TEMPLATE_FUNC_PARAMS_14 , typename FUNC_ARG_TYPE_1, typename FUNC_ARG_TYPE_2, typename FUNC_ARG_TYPE_3, typename FUNC_ARG_TYPE_4, typename FUNC_ARG_TYPE_5, typename FUNC_ARG_TYPE_6, typename FUNC_ARG_TYPE_7, typename FUNC_ARG_TYPE_8, typename FUNC_ARG_TYPE_9, typename FUNC_ARG_TYPE_10, typename FUNC_ARG_TYPE_11, typename FUNC_ARG_TYPE_12, typename FUNC_ARG_TYPE_13, typename FUNC_ARG_TYPE_14
#define FUNC_BASE_TEMPLATE_FUNC_PARAMS_14 FUNC_ARG_TYPE_1, FUNC_ARG_TYPE_2, FUNC_ARG_TYPE_3, FUNC_ARG_TYPE_4, FUNC_ARG_TYPE_5, FUNC_ARG_TYPE_6, FUNC_ARG_TYPE_7, FUNC_ARG_TYPE_8, FUNC_ARG_TYPE_9, FUNC_ARG_TYPE_10, FUNC_ARG_TYPE_11, FUNC_ARG_TYPE_12, FUNC_ARG_TYPE_13, FUNC_ARG_TYPE_14
#define FUNC_VALIDATION_STRING_14 Q_snprintf(pString, nBufLen, "method( %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s )", typeid(ARG_TYPE_1).name(), typeid(ARG_TYPE_2).name(), typeid(ARG_TYPE_3).name(), typeid(ARG_TYPE_4).name(), typeid(ARG_TYPE_5).name(), typeid(ARG_TYPE_6).name(), typeid(ARG_TYPE_7).name(), typeid(ARG_TYPE_8).name(), typeid(ARG_TYPE_9).name(), typeid(ARG_TYPE_10).name(), typeid(ARG_TYPE_11).name(), typeid(ARG_TYPE_12).name(), typeid(ARG_TYPE_13).name(), typeid(ARG_TYPE_14).name());

#define FUNC_GENERATE_ALL_BUT0(INNERMACRONAME) \
    INNERMACRONAME(1);                         \
    INNERMACRONAME(2);                         \
    INNERMACRONAME(3);                         \
    INNERMACRONAME(4);                         \
    INNERMACRONAME(5);                         \
    INNERMACRONAME(6);                         \
    INNERMACRONAME(7);                         \
    INNERMACRONAME(8);                         \
    INNERMACRONAME(9);                         \
    INNERMACRONAME(10);                        \
    INNERMACRONAME(11);                        \
    INNERMACRONAME(12);                        \
    INNERMACRONAME(13);                        \
    INNERMACRONAME(14)

#define FUNC_GENERATE_ALL(INNERMACRONAME) \
    INNERMACRONAME(0);                    \
    FUNC_GENERATE_ALL_BUT0(INNERMACRONAME)
#pragma endregion