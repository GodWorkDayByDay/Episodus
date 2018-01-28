Installation du Pilot dans Nautilus
-----------------------------------
- Installer une machine virtuelle Java Version 1.4.1 (ou sup�rieure)
  Pour cela lancer l'ex�cutable j2sdk-1_4_1-windows-i586.exe qui se trouve
  sur \\ariane\dominique

- Ajout des variables d'environnement
	Dans le PATH ajout de :
		c:\j2sdk1.4.1\bin
		c:\j2sdk1.4.1\jre\bin\server
	Variable JAVA_HOME (peut-�tre pas n�cessaire ...) :
		c:\j2sdk1.4.1	
	
- Installer le pilot :
  a) les packages Java 
	dom.jar
	jdom.jar
	netTools.jar
	pilot.jar
	servlet.jar
	tools.jar
	xercesImpl.jar
	xmlParserAPIs.jar
	
  b) le fichier de la DTD d�crivant les services
	Service.DTD

  En fait, prendre le r�pertoire C:/Pilot d'une machine de "r�f�rence" et 
  recopier ce r�pertoire sur la machine � installer

- Ajout dans le CVS de nautilus :
  a) cr�ation dans cvs/nautilus d'un r�pertoire pilot  
     et d'un r�pertoire sous include

  b) copie des fichiers : 
	Pilot.hpp
	Pilot.cpp
	NautilusPilot.hpp
	NautilusPilot.cpp
	JavaSystem.hpp
	JavaSystem.cpp

  c) localisation des fichiers Java pour JNI en ajoutant les chemins 
     dans les options de builder :
	- pour les include jni.h etc...
		c:\j2sdk1.4.1\include
		c:\j2sdk1.4.1\include\win32
	- pour la librairie jvm.lib
		c:\j2sdk1.4.1\lib

- Configuration du Pilot
	Mise � jour du fichier Pilot.properties
  Ce fichier doit �tre plac� sur la racine du nmsClient.exe 