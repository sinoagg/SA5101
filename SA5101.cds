<distribution version="17.0.0" name="SA5101" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{D32DAB8E-1CCA-4594-B29E-D98FFE8DFFEE}">
		<general appName="SA5101" outputLocation="e:\Projects\Project_SA5101_V1.8\cvidistkit.SA5101" relOutputLocation="cvidistkit.SA5101" outputLocationWithVars="e:\Projects\Project_SA5101_V1.8\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.4">
			<arp company="Microsoft" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="English" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="SA5101" welcomeText=""/></userinterface>
		<dirs appDirID="101">
			<installDir name="SA5101" dirID="100" parentID="7" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="SA5101" dirID="101" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Resource" dirID="102" parentID="106" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="SA5101" dirID="103" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="updates" dirID="104" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Uir" dirID="105" parentID="106" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="softwareFileBackups" dirID="106" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Desktop]" dirID="0" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Graph_pressed.ico" relSourcePath="Resource\Graph_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Arrow.ico" relSourcePath="Resource\Arrow.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Settings.ico" relSourcePath="Resource\Settings.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Table_pressed.ico" relSourcePath="Resource\Table_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="4" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\print.ico" relSourcePath="Resource\print.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="5" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\bg_press.ico" relSourcePath="Resource\bg_press.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="6" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Projects.ico" relSourcePath="Resource\Projects.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="7" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\D-ouGraph.ico" relSourcePath="Resource\D-ouGraph.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="8" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\FET_ico.ico" relSourcePath="Resource\FET_ico.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="9" sourcePath="e:\Projects\Project_SA5101_V1.8\cvibuild.SA5101\Release\SA5101.exe" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="10" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\DNPV.uir" relSourcePath="UI Files\panel\DNPV.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="11" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Environment.uir" relSourcePath="UI Files\panel\Environment.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="12" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\GND.ico" relSourcePath="Resource\GND.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="13" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Select_pressed.ico" relSourcePath="Resource\Select_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="14" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Table.ico" relSourcePath="Resource\Table.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="15" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Wbg.ico" relSourcePath="Resource\Wbg.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="16" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Tools.ico" relSourcePath="Resource\Tools.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="17" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Stop.ico" relSourcePath="Resource\Stop.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="18" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\RunM.ico" relSourcePath="Resource\RunM.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="19" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\gate.png" relSourcePath="Resource\gate.png" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="20" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Configure_pressed.ico" relSourcePath="Resource\Configure_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="21" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\RunAgain.ico" relSourcePath="Resource\RunAgain.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="22" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\bg.ico" relSourcePath="Resource\bg.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="23" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\ResultDispPanel.uir" relSourcePath="UI Files\panel\ResultDispPanel.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="24" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\NPV.uir" relSourcePath="UI Files\panel\NPV.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="25" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Experiment List.uir" relSourcePath="UI Files\panel\Experiment List.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="26" sourcePath="E:\Projects\Project_SA6101_V6.0\updates\localInfo.xml" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="27" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Result Menu.uir" relSourcePath="UI Files\panel\Result Menu.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="28" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Sample Configuration.uir" relSourcePath="UI Files\panel\Sample Configuration.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="29" sourcePath="E:\Projects\Project_SA6101_V6.0\updates\updateInfo.xml" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="30" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\MainPanel.uir" relSourcePath="UI Files\panel\MainPanel.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="31" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\ProjectPanel.uir" relSourcePath="UI Files\panel\ProjectPanel.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="32" sourcePath="E:\Projects\Project_SA6101_V6.0\updates\replace.exe" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="33" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\print_pressed.ico" relSourcePath="Resource\print_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="34" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\5101.ico" relSourcePath="Resource\5101.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="35" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Pic.ico" relSourcePath="Resource\Pic.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="36" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\DPV.uir" relSourcePath="UI Files\panel\DPV.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="37" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\DNPV.uir" relSourcePath="UI Files\panel\DNPV.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="38" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\saveData_pressed.ico" relSourcePath="Resource\saveData_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="39" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Table.uir" relSourcePath="UI Files\panel\Table.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="40" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\GraphDisp.uir" relSourcePath="UI Files\panel\GraphDisp.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="41" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\R.bmp" relSourcePath="Resource\R.bmp" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="42" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\no.ico" relSourcePath="Resource\no.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="43" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\DoubleGraph.ico" relSourcePath="Resource\DoubleGraph.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="44" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Run.ico" relSourcePath="Resource\Run.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="45" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\BTN.ico" relSourcePath="Resource\BTN.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="46" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Analyze_pressed.ico" relSourcePath="Resource\Analyze_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="47" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Drain.png" relSourcePath="Resource\Drain.png" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="48" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Run副本.ico" relSourcePath="Resource\Run副本.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="49" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\analyze.ico" relSourcePath="Resource\analyze.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="50" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\FET.ico" relSourcePath="Resource\FET.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="51" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\bg_pressed.ico" relSourcePath="Resource\bg_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="52" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\gate_pressed.png" relSourcePath="Resource\gate_pressed.png" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="53" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Save.ico" relSourcePath="Resource\Save.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="54" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\saveData.ico" relSourcePath="Resource\saveData.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="55" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\SA5101.png" relSourcePath="Resource\SA5101.png" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="56" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Save_pressed.ico" relSourcePath="Resource\Save_pressed.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="57" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Drain_pressed.png" relSourcePath="Resource\Drain_pressed.png" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="58" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Graph.ico" relSourcePath="Resource\Graph.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="59" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Select.ico" relSourcePath="Resource\Select.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="60" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Experiment List.uir" relSourcePath="UI Files\panel\Experiment List.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="61" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\NPV.uir" relSourcePath="UI Files\panel\NPV.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="62" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\LSV.uir" relSourcePath="UI Files\panel\LSV.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="63" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\ResultDispPanel.uir" relSourcePath="UI Files\panel\ResultDispPanel.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="64" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Settings.uir" relSourcePath="UI Files\panel\Settings.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="65" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Sample Configuration.uir" relSourcePath="UI Files\panel\Sample Configuration.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="66" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\DPV.uir" relSourcePath="UI Files\panel\DPV.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="67" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\GraphDisp.uir" relSourcePath="UI Files\panel\GraphDisp.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="68" sourcePath="E:\Projects\Project_SA5101_V1.7\systemClose.ini" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="69" sourcePath="E:\Projects\Project_SA5101_V1.7\ReadMe.txt" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="70" sourcePath="E:\Projects\Project_SA5101_V1.7\abnormalDataCache.xls" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="71" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\MainPanel.uir" relSourcePath="UI Files\panel\MainPanel.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="72" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Terminal.uir" relSourcePath="UI Files\panel\Terminal.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="73" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\TAFEL.uir" relSourcePath="UI Files\panel\TAFEL.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="74" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Table.uir" relSourcePath="UI Files\panel\Table.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="75" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\ProjectPanel.uir" relSourcePath="UI Files\panel\ProjectPanel.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="76" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Result Menu.uir" relSourcePath="UI Files\panel\Result Menu.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="77" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\IMP.uir" relSourcePath="UI Files\panel\IMP.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="78" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\I-T.uir" relSourcePath="UI Files\panel\I-T.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="79" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\C-V.uir" relSourcePath="UI Files\panel\C-V.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="80" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\SWV.uir" relSourcePath="UI Files\panel\SWV.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="81" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\SV.uir" relSourcePath="UI Files\panel\SV.uir" relSourceBase="0" targetDir="103" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="82" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\TAFEL.uir" relSourcePath="UI Files\panel\TAFEL.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="83" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\I-T.uir" relSourcePath="UI Files\panel\I-T.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="84" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Settings.uir" relSourcePath="UI Files\panel\Settings.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="85" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\SWV.uir" relSourcePath="UI Files\panel\SWV.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="86" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\LSV.uir" relSourcePath="UI Files\panel\LSV.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="87" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\0b5f76e6304de51436b2a3c882ad751.bmp" relSourcePath="Resource\0b5f76e6304de51436b2a3c882ad751.bmp" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="88" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Environment.uir" relSourcePath="UI Files\panel\Environment.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="89" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\SV.uir" relSourcePath="UI Files\panel\SV.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="90" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\C-V.uir" relSourcePath="UI Files\panel\C-V.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="91" sourcePath="e:\Projects\Project_SA5101_V1.8\Resource\Configure.ico" relSourcePath="Resource\Configure.ico" relSourceBase="0" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="92" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\IMP.uir" relSourcePath="UI Files\panel\IMP.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="93" sourcePath="e:\Projects\Project_SA5101_V1.8\UI Files\panel\Terminal.uir" relSourcePath="UI Files\panel\Terminal.uir" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="103" projectID="0">
				<fileID>9</fileID></projectOutput>
			<projectDependencies dirID="103" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="SA5101" targetFileID="9" destDirID="100" cmdLineArgs="" description="" runStyle="NORMAL"/>
			<shortcut name="SA5101" targetFileID="9" destDirID="0" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules>
			<nireports></nireports>
			<graph3d></graph3d></mergemodules>
		<products>
			<product name="NI LabVIEW Runtime 2017" UC="{620DBAE1-B159-4204-8186-0813C8A6434C}" productID="{AF2FEF05-E895-4750-8F69-B5FA5388B2A3}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49153">
				<cutSoftDeps/></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime 2017" UC="{3047BAC4-D68B-48CB-838D-2E10761B01BA}" productID="{7D090F57-E9A4-4229-9911-CC352128D3F5}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49155"/>
			<product name="NI Launcher" UC="{7FB990C5-1A51-4C1D-99C4-C6E50368E105}" productID="{2C151359-0420-401D-9408-6523BE6C3EE8}" path="D:\NILWCVI2017\" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49154"/>
			<product name="NI TDM Excel Add-In" UC="{6D2EBDAF-6CCD-44F3-B767-4DF9E0F2037B}" productID="{9DFD2D10-299D-4A37-9267-4F28E974F403}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49155"/>
			<product name="NI Variable Engine 2017" UC="{EB7A3C81-1C0F-4495-8CE5-0A427E4E6285}" productID="{3011FA37-DCC4-4BF8-8900-12D68EC7996F}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49152"/></products>
		<runtimeEngine installToAppDir="false" activeXsup="false" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="false">
			<hasSoftDeps/>
			<doNotAutoSelect>
			<component>activeXsup</component>
			<component>rtutilsup</component>
			</doNotAutoSelect></runtimeEngine><sxsRuntimeEngine>
			<selected>true</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WIN7_SP1</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="3D Graph Control Support" UC="{578B3422-EAE6-428C-A17A-7549578FE2C1}" productID="{36E48952-DC01-4739-848E-EA7DC71FB485}" path="(None)" flavorID="Full" flavorName="Full" verRestr="false" coreVer="8.63.49152">
				<dependencies>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{6EFCD9C0-82FC-4C51-B7F4-3377B6D03BA6}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime (Current Version)" UC="{CF830703-BC3D-4feb-891F-6FF27153C204}" productID="{7D090F57-E9A4-4229-9911-CC352128D3F5}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49155">
				<dependencies>
					<productID>{12DD771D-D906-470D-83D8-E443B3726E65}</productID>
					<productID>{13774AE4-124D-48C2-A8AC-F8070918385E}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{646B4AEC-1DCD-450D-A27E-2FCC02CC071D}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EFCD9C0-82FC-4C51-B7F4-3377B6D03BA6}</productID>
					<productID>{81CF68C8-142B-443E-9B96-0B38E2997D88}</productID>
					<productID>{92F3B1E4-20BE-44F2-8D2F-F0335FE172A2}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{ACA04902-B834-4355-88DA-ECDC9EA75900}</productID>
					<productID>{BCFF276A-C527-4D21-AB9B-2EE8ABB9430C}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D0078EF1-0008-4D30-83AF-4C56D2516E55}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{D4E86102-76C1-458C-B0C2-F42B43CAD3CC}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DBAAC357-96E7-459F-B115-B14E29F652EF}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{EAA77133-1A74-45EE-97FB-D67B38720514}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI Variable Engine 2017" UC="{EB7A3C81-1C0F-4495-8CE5-0A427E4E6285}" productID="{3011FA37-DCC4-4BF8-8900-12D68EC7996F}" path="(None)" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49152">
				<dependencies>
					<productID>{26B72B11-2EF9-4F28-9D4B-9ABD3E854149}</productID>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EFCD9C0-82FC-4C51-B7F4-3377B6D03BA6}</productID>
					<productID>{78C76251-4DA2-4142-9C57-933B559F6E18}</productID>
					<productID>{92F3B1E4-20BE-44F2-8D2F-F0335FE172A2}</productID>
					<productID>{9A1C4805-EB50-44F1-87C7-29F5574B44E4}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DDFE3456-19AC-42FC-92C1-CFC10E43A97D}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI TDM Excel Add-In" UC="{6D2EBDAF-6CCD-44F3-B767-4DF9E0F2037B}" productID="{9DFD2D10-299D-4A37-9267-4F28E974F403}" path="(None)" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49155">
				<dependencies>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{6EFCD9C0-82FC-4C51-B7F4-3377B6D03BA6}</productID>
					<productID>{92F3B1E4-20BE-44F2-8D2F-F0335FE172A2}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI Launcher" UC="{7FB990C5-1A51-4C1D-99C4-C6E50368E105}" productID="{2C151359-0420-401D-9408-6523BE6C3EE8}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49154">
				<dependencies>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime 2017" UC="{3047BAC4-D68B-48CB-838D-2E10761B01BA}" productID="{7D090F57-E9A4-4229-9911-CC352128D3F5}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49155">
				<dependencies>
					<productID>{12DD771D-D906-470D-83D8-E443B3726E65}</productID>
					<productID>{13774AE4-124D-48C2-A8AC-F8070918385E}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{646B4AEC-1DCD-450D-A27E-2FCC02CC071D}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EFCD9C0-82FC-4C51-B7F4-3377B6D03BA6}</productID>
					<productID>{81CF68C8-142B-443E-9B96-0B38E2997D88}</productID>
					<productID>{92F3B1E4-20BE-44F2-8D2F-F0335FE172A2}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{ACA04902-B834-4355-88DA-ECDC9EA75900}</productID>
					<productID>{BCFF276A-C527-4D21-AB9B-2EE8ABB9430C}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D0078EF1-0008-4D30-83AF-4C56D2516E55}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{D4E86102-76C1-458C-B0C2-F42B43CAD3CC}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DBAAC357-96E7-459F-B115-B14E29F652EF}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{EAA77133-1A74-45EE-97FB-D67B38720514}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Shared Runtime 2017" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{28BFBCB6-5EEE-47F1-A894-FCD877057827}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49157">
				<dependencies>
					<productID>{13774AE4-124D-48C2-A8AC-F8070918385E}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{2D894BCB-6069-418C-BF94-8E5915D8867C}</productID>
					<productID>{2FC99AB8-F11D-4938-B14F-AC60D1016FE7}</productID>
					<productID>{35E63DC2-6BCC-48D6-A1C5-5B068DF34117}</productID>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{5E99102B-D07A-4D85-8D50-4BE55E3633A0}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EFCD9C0-82FC-4C51-B7F4-3377B6D03BA6}</productID>
					<productID>{92F3B1E4-20BE-44F2-8D2F-F0335FE172A2}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{BEA1952D-1F00-4336-9A76-C41FA181C02D}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{D4E86102-76C1-458C-B0C2-F42B43CAD3CC}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DBAAC357-96E7-459F-B115-B14E29F652EF}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{EAA77133-1A74-45EE-97FB-D67B38720514}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF35E2A2-9214-4B76-91AE-5567076AAE8C}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI LabVIEW Runtime 2017" UC="{620DBAE1-B159-4204-8186-0813C8A6434C}" productID="{AF2FEF05-E895-4750-8F69-B5FA5388B2A3}" path="(None)" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49153">
				<dependencies>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{214BEF10-ED6E-4198-A7EC-893BC3550330}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{36E48952-DC01-4739-848E-EA7DC71FB485}</productID>
					<productID>{3F73C183-4720-43B3-8181-71F55B35DE16}</productID>
					<productID>{405BA31C-3A17-47EC-9075-D18B09387C32}</productID>
					<productID>{40600E36-4921-4A62-8A07-4503C6855A66}</productID>
					<productID>{4500C77E-71CE-41A9-AD2A-B7D9C2E3397E}</productID>
					<productID>{4CDCD50F-CFCA-40FB-892A-90F526537273}</productID>
					<productID>{5DF6BA6E-A045-48FC-9AD8-39A0799FA79B}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6E6C89C3-648D-4E5C-BF2E-1534F79D2FA7}</productID>
					<productID>{6EFCD9C0-82FC-4C51-B7F4-3377B6D03BA6}</productID>
					<productID>{7A92E288-9EFF-47D2-9A44-CF00F363DA7D}</productID>
					<productID>{7BBC9D71-9E93-4E87-A529-1CAC4537175C}</productID>
					<productID>{8301A002-940A-4588-A760-043776F1CA6E}</productID>
					<productID>{92F3B1E4-20BE-44F2-8D2F-F0335FE172A2}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{B7685AF0-3026-43FA-A953-327C2185BAAF}</productID>
					<productID>{BDADF4B2-9B31-48B3-8E3E-D15047C4C8AD}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{E6891F9D-6730-4D5D-B513-1B70EDB84566}</productID>
					<productID>{E6E0A909-7F30-4EE8-A493-F0329B57B187}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID>
					<productID>{FF8EF684-CF13-4EE7-BC1D-26AB49EB0CD4}</productID></dependencies></product>
			<product name="NI-Reports Support" UC="NIReports.02FA89C0_81CC_4586_8ECB_48D58CFAC0B4" productID="2.3.0" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="2.3.0"/></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="e:\Projects\Project_SA5101_V1.8\SA5101.prj" ProjectRelativePath="SA5101.prj"/></Projects>
		<buildData progressBarRate="1.110014036446620">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.339016499999954</ProductsAdded>
				<DPConfigured>0.915743062499913</DPConfigured>
				<DPMergeModulesAdded>4.196969500000078</DPMergeModulesAdded>
				<DPClosed>8.575069312499918</DPClosed>
				<DistributionsCopied>10.147131624999831</DistributionsCopied>
				<End>90.088950874999952</End></progressTimes></buildData>
	</msi>
</distribution>
