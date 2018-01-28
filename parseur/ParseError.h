#ifndef __parseerror_h__
#define __parseerror_h__

// int iParsingError;

enum parseError {
  // next is 00
  EA_NOERROR = 0,
  EATTR_EMPTY,
  EATTR_NOEQUAL,
  EATTR_EQUAL0,
  EATTR_EQUALLAST,
  EATTR_NOVALUE,
  // next is 06
  EATTR_QUOTELAST,
  EATTR_QUOTECLOSE,
  EATTR_QUOTEFIN,
  EATTR_QUOTESPACE,
  EATTR_DQUOTELAST,
  // next is 11
  EATTR_DQUOTECLOSE,
  EATTR_DQUOTEFIN,
  EATTR_DQUOTESPACE,
  EVAL_NOCLOSE,
  EVAL_NOOPEN,
  // next is 16
  EVAL_SPACE,
  EVAL_CLOSE,
  EVAL_CLOSEBALISE,
  EVAL_DEF,
  EPMED_ADMIN_DATA_ATTR,
  // next is 21
  EPMED_ADMIN_DATA_NB,
  EPMED_ADMIN_DATA_VAL,
  EPMED_ADMIN_DATA_SEXE,
  EPMED_CONTACT_ATTR,
  EPMED_CONTACT_NB,
  // next is 26
  EPMED_CONTACT_VAL,
  EPMED_CONTACT_NBVAL,
  EPMED_CONTACT_TYPE_ATTR,
  EPMED_CONTACT_TYPE_NB,
  EPMED_CONTACT_TYPE_VAL,
  // next is 31
  EPMED_CONTACT_TYPE_CONDITIONS,
  EPMED_CONTACT_TYPE_RENDEZ_VOUS,
  EPMED_CONTACT_CODE_ATTR,
  EPMED_CONTACT_CODE_NBATTR,
  EPMED_CONTACT_CODE_VAL,
  // next is 36
  PMED_CONTACT_CODE_POSITION,
  PMED_CONTACT_CODE_CLASSIFICATION,
  PMED_CONTACT_CODE_CLASSIFICATION_BIS,
  EPMED_CONTACT_ELT_ATTR,
  EPMED_CONTACT_ELT_NBATTR,
  // next is 41
  EPMED_CONTACT_ELT_VAL_FALSE,
  EPMED_CONTACT_ELT_VAL,
  EPMED_CONTACT_PRINCIPE,
  EPMED_HEALTH_DATA_EMPTY,
  EPMED_HEALTH_DATA_VAL,
  // next is 46
  EPMED_MESSAGE_EMPTY,
  EPMED_MESSAGE_ATTR,
  EPMED_MESSAGE_NBATTR,
  EPMED_MESSAGE_VAL_EMPTY,
  EPMED_MESSAGE_VAL,
  // next is 51
  EPMED_MESSAGE_NBVAL,
  EPMED_PATIENT_ATTR_EMPTY,
  EPMED_PATIENT_ATTR,
  EPMED_PATIENT_NBATTR,
  EPMED_PATIENT_VAL,
  // next is 56
  EPMED_PATIENT_NBVAL,
  EPMED_PROBLEM_ATTR_EMPTY,
  EPMED_PROBLEM_ATTR,
  EPMED_PROBLEM_NBATTR,
  EPMED_PROBLEM_VAL,
  // next is 61
  EPMED_PROBLEM_EVENT_ATTR_EMPTY,
  EPMED_PROBLEM_EVENT_ATTR,
  EPMED_PROBLEM_EVENT_NBATTR,
  EPMED_PROBLEM_EVENT_VAL,
  EPMED_PROBLEM_EVENT_TYPE,
  // next is 66
  EPMED_PROBLEM_EVENT_IMPORTANT,
  EMESSAGE_EMPTY,
  EMESSAGE_BALISE_FIN,
  EMESSAGE_BALISE_DEBUT_FERMANTE,
  EMESSAGE_BALISE_DEBUT,
  // next is 71
  EPMED_UNKNOWN_SENDER,
  EPMED_WRONG_CLASSIF_PRINCIPLE,
  EPMED_CONTACTTREE_ATTR,
  EPMED_CONTACTTREE_VAL,
  EPMED_CONTACTTREE_VAL_FALSE,
  // next is 76
  EPMED_CONTACTTREE_NBATTR,
  EPMED_CONTACTNODE_ATTR,
  EPMED_CONTACTNODE_VAL,
  EPMED_CONTACTNODE_NBATTR
} ;

#ifdef TRALALA
enum parseError { EA_NOERROR = 0, EATTR_EMPTY, EATTR_NOEQUAL, EATTR_EQUAL0, EATTR_EQUALLAST, EATTR_NOVALUE,
		  /* 6 */ EATTR_QUOTELAST,EATTR_QUOTECLOSE, EATTR_QUOTEFIN, EATTR_QUOTESPACE, EATTR_DQUOTELAST,
		  /* 11 */ EATTR_DQUOTECLOSE, EATTR_DQUOTEFIN, EATTR_DQUOTESPACE,
		  /* 16 */ EVAL_NOCLOSE, EVAL_NOOPEN, EVAL_SPACE, EVAL_CLOSE, EVAL_CLOSEBALISE,
		  /* 21 */ EVAL_DEF, EPMED_ADMIN_DATA_ATTR, EPMED_ADMIN_DATA_NB, EPMED_ADMIN_DATA_VAL, EPMED_ADMIN_DATA_SEXE,
		  /* 26 */ EPMED_CONTACT_ATTR, EPMED_CONTACT_NB, EPMED_CONTACT_VAL, EPMED_CONTACT_NBVAL, EPMED_CONTACT_TYPE_ATTR,
		  /* 31 */ EPMED_CONTACT_TYPE_NB, EPMED_CONTACT_TYPE_VAL, EPMED_CONTACT_TYPE_CONDITIONS, EPMED_CONTACT_TYPE_RENDEZ_VOUS, EPMED_CONTACT_CODE_ATTR,
		  /* 36 */ EPMED_CONTACT_CODE_NBATTR, EPMED_CONTACT_CODE_VAL, PMED_CONTACT_CODE_POSITION, PMED_CONTACT_CODE_CLASSIFICATION, PMED_CONTACT_CODE_CLASSIFICATION_BIS,
		  /* 41 */ EPMED_CONTACT_ELT_ATTR, EPMED_CONTACT_ELT_NBATTR, EPMED_CONTACT_ELT_VAL_FALSE, EPMED_CONTACT_ELT_VAL, EPMED_CONTACT_PRINCIPE,
		  /* 46 */ EPMED_HEALTH_DATA_EMPTY, EPMED_HEALTH_DATA_VAL, EPMED_MESSAGE_EMPTY, EPMED_MESSAGE_ATTR, EPMED_MESSAGE_NBATTR,
		  /* 51 */ EPMED_MESSAGE_VAL_EMPTY, EPMED_MESSAGE_VAL,
		  /* 56 */ EPMED_MESSAGE_NBVAL, EPMED_PATIENT_ATTR_EMPTY, EPMED_PATIENT_ATTR, EPMED_PATIENT_NBATTR, EPMED_PATIENT_VAL,
		  /* 61 */ EPMED_PATIENT_NBVAL, EPMED_PROBLEM_ATTR_EMPTY, EPMED_PROBLEM_ATTR, EPMED_PROBLEM_NBATTR, EPMED_PROBLEM_VAL,
		  /* 66 */ EPMED_PROBLEM_EVENT_ATTR_EMPTY, EPMED_PROBLEM_EVENT_ATTR, EPMED_PROBLEM_EVENT_NBATTR, EPMED_PROBLEM_EVENT_VAL, EPMED_PROBLEM_EVENT_TYPE,
		  /* 71 */ EPMED_PROBLEM_EVENT_IMPORTANT, EMESSAGE_EMPTY, EMESSAGE_BALISE_FIN, EMESSAGE_BALISE_DEBUT_FERMANTE, EMESSAGE_BALISE_DEBUT };
#endif

#endif