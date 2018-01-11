# Author:avikulin
# Description: 
# Use this script to generate/update parameter "includePath" in {/.vscode/c_cpp_properties.json}

tree -ifdvQ --nolinks -I "*build"|sed -r 's|([.][/])|${workspaceRoot}/|g'|sed -r 's|["]$|",|g'>directorystruct.txt