# Checks output of the hudson/jenkins CI and sends signal to "buildwatch"
# extreme feedback device that lights up LEDs with proper color.
#
# This code is in the public domain. 

# configuration
$JENKINS_ADDRESS = "http://localhost:8080/api/xml"
$PORT_NAME = "COM6"

# colors contained in xml from jenkins/hudson
$WARNING_COLORS = @("yellow", "yellow_anime")
$FAILING_COLORS = @("red", "red_anime")

# colors send to arduino
$GREEN_LIGHT_COLOR = 'g'
$YELLOW_LIGHT_COLOR = 'y'
$RED_LIGHT_COLOR = 'r'

# arduino communication constants
$BAUD_RATE = "9600"
$PARITY = "None"

# determine lightColor from hudson's XML
Try {
	# get xml from jenkins
	$xml = New-Object System.Xml.XmlDocument
	$xml.Load($JENKINS_ADDRESS)

	# IMPORTANT: 
	# change "hudson" to "listView" when parsing only selected view
	$jobs = $xml.hudson.job

	# initialize to green
	$lightColor = $GREEN_LIGHT_COLOR

	# search for jobs with warning
	$warningJobs = $jobs | where {$WARNING_COLORS -contains $_.color} | measure
	if ($warningJobs.Count -ne 0) {
		$lightColor = $YELLOW_LIGHT_COLOR
	}

	# search for jobs with errors
	$failingJobs = $jobs | where {$FAILING_COLORS -contains $_.color} | measure
	if ($failingJobs.Count -ne 0) {  
		$lightColor = $RED_LIGHT_COLOR
	}
} Catch {
	# fallback - when any exception occurs set light to red
	$lightColor = $RED_LIGHT_COLOR
}

# send lightColor to arduino
$port = New-Object System.IO.Ports.SerialPort
$port.PortName = $PORT_NAME
$port.BaudRate = $BAUD_RATE
$port.Parity = $PARITY

$port.Open()
$port.Write($lightColor)
$port.Close()
