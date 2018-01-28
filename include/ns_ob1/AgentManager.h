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
#ifndef __AGENT_MANAGER__HH_
#define  __AGENT_MANAGER__HH_

#include "ns_ob1/agent.h"

/**
* Used to Parse Agent XML File
*/
#include "nsutil\tinyxml.h"

/**
* \brief The goal is to give an Agent XML loader
*/
/**
* The goal is to give an Agent XML loader <BR>
* Le but de ce fichier est de fournir une interface pour la cr�ation
* d'un agent � a partir d'un fichier script XML
*/
class AgentManager
{
 public:
 		/**
    * \brief Constructor
    */
    /**
    * Constructor
    */
    AgentManager();

    /**
    * Create an agent from an xml script file <BR>
    * Cr�e un agent � partir d'un script
    * @param xmlNam XLM file'name
    * @return The agent
    */
		AgentScript* create_agent_from_script(std::string xmlName);
 private:
 		/**
    * parse declaration part of an XML script  <BR>
  	* Fonction parsant la d�claration du fichier XML
    * @param node Cml subtree to parse
    * @param ag  Agent to fill
    * @return return true if no parse error and false else
    */
 		bool 	ParseDescription(TiXmlNode* node, AgentScript* ag);

    /**
  	* \brief Fonction parsant la partie communication avec le controler du fichier XML
    */
    /**
    * Fonction parsant la partie communication avec le controler du fichier XML <BR>
    * @param node noeud xml a parser
    * @param ag agent a remplir
    * @return  true si le parse c'est d�roul� correctement et false sinon
    */
 		bool 	ParseCommunicationWithScript(TiXmlNode* node, AgentScript* ag);

    /**
    * \brief Fonction parsant la partie liant l'interpreteur et le KSG
    */
    /**
  	* Fonction parsant la partie liant l'interpreteur et le KSG
    * @param node noeud xml a parser
    * @param ag agent a remplir
    * @return  true si le parse c'est d�roul� correctement et false sinon
    */
 		bool 	ParseCommunicationWithInterpreter(TiXmlNode* node, AgentScript* ag);

    /**
    * \brief Fonction parsant la partie code du script
    */
    /**
  	* Fonction parsant la partie code du script
    * @param node noeud xml a parser
    * @param ag agent a remplir
    * @return  true si le parse c'est d�roul� correctement et false sinon
    */
 		bool 	ParseCode(TiXmlNode* node, AgentScript* ag);

};



#endif
