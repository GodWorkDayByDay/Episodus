/*
** Copyright Nautilus, (10/9/2004)
** david.giocanti@nautilus-info.com

** Ce logiciel est un programme informatique servant � [rappeler les
** caract�ristiques techniques de votre logiciel].

** Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
** respectant les principes de diffusion des logiciels libres. Vous pouvez
** utiliser, modifier et/ou redistribuer ce programme sous les conditions
** de la licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA
** sur le site "http://www.cecill.info".

** En contrepartie de l'accessibilit� au code source et des droits de copie,
** de modification et de redistribution accord�s par cette licence, il n'est
** offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
** seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
** titulaire des droits patrimoniaux et les conc�dants successifs.

** A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
** associ�s au chargement,  � l'utilisation,  � la modification et/ou au
** d�veloppement et � la reproduction du logiciel par l'utilisateur �tant
** donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
** manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
** avertis poss�dant  des  connaissances  informatiques approfondies.  Les
** utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
** logiciel � leurs besoins dans des conditions permettant d'assurer la
** s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
** � l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.

** Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez
** pris connaissance de la licence CeCILL, et que vous en avez accept� les
** termes.
*/

#include "ns_ob1\InitStructure.h"
#include "ns_ob1\BB1Types.h"
#include "ns_ob1\TypedVal.h"

INode::INode(TypedVal* label, std::string classo, std::string clasorm)
{
  _labeled   = label ;
  _classTo   = classo ;
  _classFrom = clasorm ;
}

INode::INode(const INode& temp)
{
  _labeled   = temp._labeled ;
  _classFrom = temp._classFrom ;
  _classTo   = temp._classTo ;
}

INode&
INode::operator=(const INode& src)
{
	if (&src == this)
		return *this ;

  _labeled   = src._labeled ;
  _classFrom = src._classFrom ;
  _classTo   = src._classTo ;

  return *this ;
}

INode::~INode()
{
  if (_labeled)
    delete _labeled ;
}

std::string INode::toHTML()
{
  std::string result = std::string("") ;
  //result= "[INODE : (" + labeled +"," + classType + ")]<br />";
  return result ;
}

/*
** Default constructeur
*/
Level::Level()
{
  _complexity = 0 ;
  _quality    = 0 ;
}

/*
** Destructeur
*/
Level::~Level()
{
	if (false == _level.empty())
  {
		for (size_t i = 0 ; i < _level.size() ; i++)
    	if (_level[i])
      	delete _level[i] ;
  }
}

Level::Level(int complex, int qualit)
      :_complexity(complex), _quality(qualit)
{
}

/*
** Copy constructor
*/
Level::Level(const Level& lev)
      :_complexity(lev.Complexity()), _quality(lev.Quality())
{
  if (false == lev._level.empty())
    for (size_t i = 0 ; i < lev._level.size() ; i++)
      _level.push_back(new INode(*(lev._level[i]))) ;
}

Level&
Level::operator=(const Level& src)
{
	if (&src == this)
		return *this ;

  _complexity = src._complexity ;
  _quality    = src._quality ;

  if (false == _level.empty())
  {
		for (size_t i = 0 ; i < _level.size() ; i++)
    	if (_level[i])
      	delete _level[i] ;

    _level.clear() ;
  }

  if (false == src._level.empty())
    for (size_t i = 0 ; i < src._level.size() ; i++)
      _level.push_back(new INode(*(src._level[i]))) ;

  return *this ;
}

/*
** Add an optionnal triggered condition
*/
void
Level::addLevelNode(TypedVal* tri, std::string& classto,std::string& classfrom)
{
  INode* temp = new INode(tri, classto, classfrom) ;
  _level.push_back(temp) ;
}

/*
inline INode*
Level::operator[] (size_t i)
{
  if (_level.size() <= i)
    return (INode*) 0 ;

  return _level[i] ;
} */

void
Level::print(std::ostream& ostr) const
{
  ostr << "Level" ;
}

std::string
Level::toHTML()
{
  char qualit[10] ;
  char complex[10] ;
  itoa(_quality, qualit, 10) ;
  itoa(_complexity, complex, 10) ;

  std::string temp = "<br />[Level <br /> \n" ;

  temp += "<ul><li>quality:" ;
  temp.append(qualit) ;
  temp  += "</li><li>Complexity :" ;
  temp.append(complex) ;
  temp += "</li><li><ul>" ;
  for (unsigned int i = 0 ; i < _level.size() ; i++)
    temp += _level[i]->toHTML() ;
  temp+="]<br /></ul></li></ul>EndLevel]<br />" ;

  return temp ;
}

/*
** Default constructor
*/
KsInitStructure::KsInitStructure()
{
  _ksName      = std::string("") ;
	_ValidityVar = (Level*) 0 ;
	_Required    = (Level*) 0 ;
  _ksType      = KS_UNDEFINED ;
}

/*
** Default constructor
*/
KsInitStructure::KsInitStructure(char* name)
{
  _ksName      = std::string(name) ;
  _ValidityVar = (Level*) 0 ;
  _Required    = (Level*) 0 ;
  _ksType      = KS_UNDEFINED ;
}

/*
** Destructor of  KsInitStructure
** Destroy all the data contains in the class
*/
KsInitStructure::~KsInitStructure()
{
  if (false == _Levels.empty())
    for (size_t i = 0 ; i < _Levels.size() ; i++)
      delete _Levels[i] ;

  if (false == _Result.empty())
    for (size_t i = 0 ; i < _Result.size() ; i++)
      delete _Result[i] ;

  if (_Required)
    delete _Required ;
  if (_ValidityVar)
    delete _ValidityVar ;

  if (false == _Trigerred.empty())
    for (size_t i = 0 ; i < _Trigerred.size() ; i++)
      delete _Trigerred[i] ;
}

/*
** overloading of operator =
*/
KsInitStructure&
KsInitStructure::operator=(const KsInitStructure &temp)
{
  if (&temp == this)
		return *this ;

  // _Levels
  //
  if (false == _Levels.empty())
    for (size_t i = 0 ; i < _Levels.size() ; i++)
      delete _Levels[i] ;

  _Levels.clear() ;

  if (false == temp._Levels.empty())
    for (size_t i = 0 ; i < temp._Levels.size() ; i++)
      _Levels.push_back(new Level(*(temp._Levels[i]))) ;

  // _Result
  //
  if (false == _Result.empty())
    for (size_t i = 0 ; i < _Result.size() ; i++)
      delete _Result[i] ;

  _Result.clear() ;

  if (false == temp._Result.empty())
    for (size_t i = 0 ; i < temp._Result.size() ; i++)
      _Result.push_back(new INode(*(temp._Result[i]))) ;

  if (_Required)
    delete _Required ;
  if (temp._Required)
    _Required = new Level(*(temp._Required)) ;
  else
    _Required = (Level*) 0 ;

  if (_ValidityVar)
    delete _ValidityVar ;
  if (temp._ValidityVar)
    _ValidityVar = new Level(*(temp._ValidityVar)) ;
  else
    _ValidityVar = (Level*) 0 ;

  // _Trigerred
  //
  if (false == _Trigerred.empty())
    for (size_t i = 0 ; i < _Trigerred.size() ; i++)
      delete _Trigerred[i] ;

  _Trigerred.clear() ;

  if (false == temp._Trigerred.empty())
    for (size_t i = 0 ; i < temp._Trigerred.size() ; i++)
      _Trigerred.push_back(new Level(*(temp._Trigerred[i]))) ;

  _ksName = temp._ksName ;

  return *this ;
}

/*
** copy constructor
*/
KsInitStructure::KsInitStructure(const KsInitStructure& ini)
{
  if (false == ini._Levels.empty())
    for (size_t i = 0 ; i < ini._Levels.size() ; i++)
      _Levels.push_back(new Level(*(ini._Levels[i]))) ;

  if (false == ini._Trigerred.empty())
    for (size_t i = 0 ; i < ini._Trigerred.size() ; i++)
      _Trigerred.push_back(new Level(*(ini._Trigerred[i]))) ;

  if (false == ini._Result.empty())
    for (size_t i = 0 ; i < ini._Result.size() ; i++)
      _Result.push_back(new INode(*(ini._Result[i]))) ;

  if (ini._Required)
    _Required = new Level(*(ini._Required)) ;
  else
    _Required = (Level*) 0 ;

  if (ini._ValidityVar)
    _ValidityVar = new Level(*(ini._ValidityVar)) ;
  else
    _ValidityVar = (Level*) 0 ;

  _ksName = ini._ksName ;
}

inline Level*
KsInitStructure::operator[](size_t i)
{
  if (_Levels.size() <= i)
    return (Level*) 0 ;

  return _Levels[i] ;
}

/*
** return the number of level
*/
inline
int KsInitStructure::getExecutionNumber()const
{
  return _Levels.size() ;
}

std::string KsInitStructure::toHTML()
{
  std::string result = std::string("") ;
  result += std::string("<br />[InitStructure : <br />\n") ;
  result += std::string("Nom du ks : ") + _ksName + std::string("<br />") ;

  result += std::string("<br />Nombre de niveaux de trigerred condition : ") ;
  char tn[10] ;
  itoa(_Trigerred.size(), tn, 10) ;
  result.append(tn) ;

  result += std::string("<br /> ->Details -><ul>") ;
  for (size_t i = 0 ; i < _Trigerred.size() ; i++)
  {
    result += std::string("<li>") + (_Trigerred[i])->toHTML() ;
    result += std::string("</li>") ;
  }
  result += std::string("</ul><br /> \n") ;

  result += std::string("Nombre de niveaux de variables : ") ;
  char tn2[10] ;
  itoa(_Levels.size(), tn2, 10) ;
  result.append(tn2) ;

  result += std::string("<br /> ->details -> <ul>") ;
  for (size_t i = 0 ; i < _Levels.size() ; i++)
  {
    result += std::string("<li>") + (_Levels[i])->toHTML() ;
    result += std::string("</li>") ;
  }
  result += std::string("</ul><br /> \n") ;

  result += std::string("Nombre de r&eacute;sultats fournis : ") ;
  char tn3[10] ;
  itoa(_Levels.size(), tn3, 10) ;
  result.append(tn3) ;

  result += std::string("<br /> ->details -> <ul>") ;
  for (size_t i = 0 ; i < _Result.size() ; i++)
  {
    result += std::string("<li>") + (_Result[i])->toHTML() ;
    result += std::string("</li>") ;
  }
  result += std::string("</ul><br /> ]\n") ;

  return result ;
}

/*
** Return the i trigerred
*/
inline Level*
KsInitStructure::getTrigerredAtRank(size_t i)
{
  if (i >= _Trigerred.size())
    return (Level*) 0 ;

	return _Trigerred[i] ;
}

/*
** Methode naive : FIXME
*/
bool KsInitStructure::checkCourtCircuit()
{
   /*   std::vector<std::string> _buffer;
      register unsigned int i;
      unsigned int fin = _Trigerred->size();
      for (i = 0; i < fin; i++)
      {
        for (int j = 0; j <   (*_Trigerred)[i]->getLevelsize(); j++)
          {
            for (unsigned int k = 0; k < _buffer.size(); k++)
              if (_buffer[k] ==(*(*_Trigerred)[i])[j])
                return false;
            _buffer.push_back((*(*_Trigerred)[i])[j]);
          }
      }
      return true;    */
  return true ;
}

