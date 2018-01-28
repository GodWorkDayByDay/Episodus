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

#include <iostream>
#include <fstream>

#include "ns_ob1\OB1graph.h"
#include "nautilus\nssuper.h"

OB1Graph::OB1Graph(OB1Controler* pControler)
{
  _graph_size = 0 ;
  _pControler = pControler ;
}

OB1Graph::OB1Graph(const OB1Graph& inp)
{
  _graph_size = 0 ;

  putAllVertex(inp.getAllVertex()) ;
}

OB1Graph::~OB1Graph()
{
 	//save("noeud.html");

  //
  string sMsg = string("OB1Graph destructor: testing OtherNodes") ;
  // pContexte->getSuperviseur()->trace(&sMsg, 1, NSSuper::trSubDetails) ;

  testOtherNodes() ;

  sMsg = string("OB1Graph destructor: OtherNodes tested") ;
  // pContexte->getSuperviseur()->trace(&sMsg, 1, NSSuper::trSubDetails) ;

  _Ks_nodes.clear() ;
  _Other_nodes.clear() ;
  _Validity_nodes.clear() ;
  _Trigger_nodes.clear() ;
  _And_nodes.clear() ;
  _Result_Nodes.clear() ;
  _Level_node.clear() ;

  if (false == _AllNode.empty())
  {
    std::vector<OB1Node*>::iterator it = _AllNode.begin() ;
    for ( ; _AllNode.end() != it ; )
    {
      delete *it ;
      _AllNode.erase(it) ;
    }
  }
}

void
OB1Graph::testOtherNodes()
{
  std::map<std::string, OB1NOther*>::iterator oIt = _Other_nodes.begin() ;
  for ( ; _Other_nodes.end() != oIt ; oIt++)
  {
    MarkerObject* priorit = oIt->second->Attribute().get(std::string("priority")) ;
    int value = priorit->intValue() ;
  }
}

/*
** find a node in the graph
** If the node does not exsit then return -42
** else return the numero of the node int the graph
*/
int
OB1Graph::find(OB1Node* temp)
{
  register unsigned int end = numVertices() ;
  for (register unsigned int i = 0 ; i < end ; i++)
  	if (temp->Compares(_AllNode[i]))
    	return (i) ;

  return (-42) ;
}

void
OB1Graph::AddVertex(OB1Node* nod)
{
  _graph_size++ ;

  switch (nod->getType())
  {
    case KS_NODE :
      {
        OB1NKS* temp = (OB1NKS*) nod ;
        _Ks_nodes.push_back(temp) ;
      }
      break ;
    case OTHER_NODE :
      {
        std::string id = ComputeSortingId(((OB1NOther*)nod)->getPath()) ;
        _Other_nodes[id] = (OB1NOther*) nod ;
      }
      // sort(_Other_nodes->begin(),_Other_nodes->end(),tri_other);
      break ;
    case VALIDITY_NODE :
      _Validity_nodes.push_back((OB1NValidity*) nod) ;
      break ;
    case AND_NODE :
      _And_nodes.push_back((OB1NAnd*) nod) ;
      break ;
    case RESULT_NODE:
      _Result_Nodes.push_back((OB1NResult*) nod) ;
      break ;
    case LEVEL_NODE:
      _Level_node.push_back((OB1NLevel*) nod) ;
      break ;
    case TRIGGER_NODE:
      _Trigger_nodes.push_back((OB1NTrigger*) nod) ;
      break ;
  }

  _AllNode.push_back(nod) ;
}

const int OB1Graph::Degree(OB1Node& vert) const
{
	return (vert.ChildrenCardinal()) ;
}

#ifdef __OB1__UNOPTIM__
void
OB1Graph::print(std::ostream& ostr) const
{
	ostr << "Taille du graph :" << numVertices() << std::endl;
  for (unsigned int i = 0; i < _AllNode.size(); i++)
  	ostr << (*(*_AllNode)[i]) ;
}
#endif

void OB1Graph::save(std::string& FileName)
{
	ofstream file(FileName.c_str()) ;
	if (!(file.is_open()))
		return ;

  std::string temp = "<html><body BGCOLOR='663366'> <center><h1>Controler's state</h1></center><br />";

  for (unsigned int i = 0; i < (unsigned int)numVertices(); i++)
    _AllNode[i]->htmlPrint(temp) ;

  temp += "<center>number of node : " ;
  char *ta = new char[16] ;
  itoa(numVertices(), ta, 10) ;
  temp.append(ta);
  delete[] ta ;
  temp += "</center></body></html>" ;
  file << temp ;
  file.close() ;
}

/*
bool tri_other(OB1NOther* un, OB1NOther* deux)
{
  if (un->SortingId() < deux->SortingId())
    return true;
  return false;
}  */

