/*********************************************
	向服务器提交申请函数 submit()；
**********************************************/



function changeList()
{

	document.getElementById("contentList").innerHTML = "";

	state = 0;
	send("GetList","");
	beList();

	document.getElementById("contentList").innerHTML = str;
	str = "";

/*	document.getElementById("contentList").appendChild(list);*/

}


function query()
{
	var temp = sub_i;
	state = 1;
	do
	{
		if(version.options[version.selectedIndex].text == array[temp][4])
		{
			id = array[temp][3];
			break;
		}
		temp++;
	}while(temp<dataNum&&array[temp][5]);
	send("Query","id="+id);
}

function del()
{
	var temp = sub_i;
	state = 2;
	do
	{
		if(version.options[version.selectedIndex].text == array[temp][4])
		{
			id = array[temp][3];
			break;
		}
		temp++;
	}while(temp<dataNum&&array[temp][5]);
	send("Delete","id="+id);
	changeList();
}

function edit()
{
	var temp = sub_i;
	state = 3;
	for(i=sub_i;i<dataNum&&array[i][5];i++);
	maxVers = array[i-1][4];
	do
	{
		if(version.options[version.selectedIndex].text == array[temp][4])
		{
			t1 = dataArray[temp][0];
			t2 = dataArray[temp][1];
			t3 = dataArray[temp][2];
			vers = dataArray[temp][4];
			phase = 1;
			break;
		}
		temp++;
	}while(temp<dataNum&&array[temp][5]);
	cont = document.getElementById("content").value;
	send("Edit","id="+id+"&t1="+t1+"&t2="+t2+"&t3="+t3+"&phase="+phase+"&version="+vers+"&maxVersion="+maxVers+"&content="+cont);
	changeList();
}

function addUp()
{
	if(sub_i!=0)
	{
		if(trad == 1)
		{
			t1 = (parseFloat(dataArray[sub_i][0])+parseFloat(dataArray[sub_i-1][0]))/2;
			t2 = 0;
			t3 = 0;
		}
		else if(trad == 2)
		{
			t1 = dataArray[sub_i];
			t2 = (parseFloat(dataArray[sub_i][1])+parseFloat(dataArray[sub_i-1][1]))/2;
			t3 = 0;
		}
		else
		{
			t1 = dataArray[sub_i];
			t2 = dataArray[sub_i][1];
			t3 = (parseFloat(dataArray[sub_i][2])+parseFloat(dataArray[sub_i-1][2]))/2;
		}
	}
	else
	{
		t1 = dataArray[sub_i][0]/2;
		t2 = 0;
		t3 = 0;
	}
	phase = 1;
	document.getElementById("content").value = "";
}

function addDown()
{
	var j,temp=1.0;

		if(trad == 1)
		{
			for(j=sub_i+1;j<dataNum;j++)
			{
				if(dataArray[j][0]!=dataArray[sub_i][0])
				{
					temp = parseFloat(dataArray[j][0]);
					break;
				}

			}

			t1 = (parseFloat(dataArray[sub_i][0])+temp)/2;
			t2 = 0;
			t3 = 0;
		}
		else if(trad == 2)
		{
			for(j=sub_i+1;j<dataNum;j++)
			{
				if(dataArray[j][1]!=dataArray[sub_i][1]&&dataArray[j][1]!=0&&dataArray[j][0]==dataArray[sub_i][0])
				{
					temp = parseFloat(dataArray[j][1]);
					break;
				}
			}
			t1 = dataArray[sub_i][0];
			t2 = (parseFloat(dataArray[sub_i][1])+temp)/2;
			t3 = 0;
		}
		else
		{
			for(j=sub_i+1;j<dataNum;j++)
			{
				if(dataArray[j][2]!=dataArray[sub_i][2]&&dataArray[j][2]!=0&&dataArray[j][0]==dataArray[sub_i][0]&&dataArray[j][1]==dataArray[sub_i][1])
				{
					temp = parseFloat(dataArray[j][2]);
					break;
				}
			}
			t1 = dataArray[sub_i][0];
			t2 = dataArray[sub_i][1];
			t3 = (parseFloat(dataArray[sub_i][2])+temp)/2;
		}

	phase = 1;
	document.getElementById("content").value = "";
}

function addChild()
{
	var j;

	if(trad == 1)
	{
		for(j=sub_i+1;j<dataNum&&(dataArray[j][0]==dataArray[sub_i][0]);j++)
			if(dataArray[j][1]!=0)
			{
				alert("Add Failed !");
				return;
			}

		t1 = dataArray[sub_i][0];
		t2 = 0.5;
		t3 = 0;
	}
	else if(trad == 2)
	{
		for(j=sub_i+1;j<dataNum&&(dataArray[j][0]==dataArray[sub_i][0])&&(dataArray[j][1]==dataArray[sub_i][1]);j++)
		if(dataArray[j][3]!=0)
		{
			alert("Add Failed!");
			return;
		}

		t1 = dataArray[sub_i][0];
		t2 = dataArray[sub_i][1];
		t3 = 0.5;
	}else
		{
			alert("Add Failed!");
			return;
		}

	phase = 1;
	document.getElementById("content").value = "";
}

function addConfirm()
{
	state = 4;
	cont = document.getElementById("content").value;
	send("Add","t1="+t1+"&t2="+t2+"&t3="+t3+"&phase="+phase+"&content="+cont);
	changeList();
}