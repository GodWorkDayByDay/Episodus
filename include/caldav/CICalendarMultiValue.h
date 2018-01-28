/*
    Copyright (c) 2007 Cyrus Daboo. All rights reserved.
    
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
	CICalendarMultiValue.h

	Author:
	Description:	<describe the CICalendarMultiValue class here>
*/

#ifndef CICalendarMultiValue_H
#define CICalendarMultiValue_H

#include "CICalendarValue.h"

namespace iCal {

class CICalendarMultiValue : public CICalendarValue
{
public:
	CICalendarMultiValue(EICalValueType type)
		{ mType = type; }
	CICalendarMultiValue(const CICalendarMultiValue& copy)
		 : CICalendarValue(copy)
		{ _copy_CICalendarMultiValue(copy); }
	virtual ~CICalendarMultiValue()
		{ _tidy_CICalendarMultiValue(); }

	CICalendarMultiValue& operator=(const CICalendarMultiValue& copy)
		{ if (this != &copy) _copy_CICalendarMultiValue(copy); return *this; }

	virtual CICalendarValue* clone()
		{ return new CICalendarMultiValue(*this); }

	virtual EICalValueType GetType() const
		{ return mType; }
	
	const CICalendarValueList& GetValues() const
		{ return mValues; }
	CICalendarValueList& GetValues()
		{ return mValues; }
	void AddValue(CICalendarValue* value)
		{ mValues.push_back(value); }

	virtual void Parse(const cdstring& data);
	virtual void Generate(ostream& os) const;

private:
	EICalValueType		mType;
	CICalendarValueList	mValues;

	void _copy_CICalendarMultiValue(const CICalendarMultiValue& copy);
	void _tidy_CICalendarMultiValue();
};

}	// namespace iCal

#endif	// CICalendarMultiValue_H