// TODO: Find out why the SmartDashboard values aren't being put to the SmartDashboard



#include "HardwareManager.h"
#include "joystick.h"


const float HardwareManager::WHEEL_RPM_FULL_SPEED = 0.0;
const float HardwareManager::WHEEL_RADIUS = 0.0;
// What the hell is this constant Max?
const float HardwareManager::DIST_SENSOR_CONST = 0.0048828125;

HardwareManager::HardwareManager(JoystickManagerManager* jman):
    BaseManager(),
    m_finished(false),
    m_talons(),
    m_servos(),
    m_anaios(),
    m_digios(),
    m_joysticks()
{
    m_drive = NULL;
    m_jman = jman;
    m_internal_timer = new Timer();
}

HardwareManager::HardwareManager():
    BaseManager(),
    m_finished(false),
    m_talons(),
    m_servos(),
    m_anaios(),
    m_digios(),
    m_joysticks()
{
    m_drive = NULL;
    m_jman = NULL;
    m_internal_timer = new Timer();
}

HardwareManager::~HardwareManager(){
}

int HardwareManager::Init(){
    log_info("Beginning HardwareManager Initialization.");
    //this->addTalon(0,"frontLeft");
    log_info("Adding CANTalon frontLeft at ID=0");
    this->m_talons["frontLeft"] = new CANTalon(0);
    log_info("Adding CANTalon backLeft at ID=1");
    this->m_talons["backLeft"] = new CANTalon(1);
    log_info("Adding CANTalon frontRight at ID=2");
    this->m_talons["frontRight"] = new CANTalon(2);
    log_info("Adding CANTalon backRight at ID=3");
    this->m_talons["backRight"] = new CANTalon(3);
    log_info("Adding CANTalon intake at ID=4");
    this->m_talons["intake"] = new CANTalon(4);
    
    log_info("Adding Talon leftShoot at ID=9");
    this->m_talons["leftShoot"] = new Talon(9);
    log_info("Adding Talon rightShoot at ID=8");
    this->m_talons["rightShoot"] = new Talon(8);
    log_info("Adding Talon armExtRet at ID=1");
    this->m_talons["armExtRet"] = new Talon(1);
    log_info("Adding Talon armUpDown at ID=2");
    this->m_talons["armUpDown"] = new Talon(2);

    log_info("Adding Talon TESTTALON at ID=3");
    this->m_talons["TESTTALON"] = new Talon(3);

    log_info("Registering Servos.");
    log_info("Adding Servo TESTSERVO at ID=0");
    this->m_servos["TESTSERVO"] = new Servo(0);

    log_info("Adding Servo WinchActive at ID=5");
    this->m_servos["WinchActivate"] = new Servo(5);

    /*
    log_info("Adding Servo IntakeArmActivate at ID=2");
    this->m_servos["IntakeArmActivate"] = new Servo(6);
    */

    log_info("Adding Servo flap thing at ID=7");
    this->m_servos["flap thing"] = new Servo(7);

    log_info("Registering Analog Channels.");
    log_info("Adding AnalogChannel dist_sensor at ID=0");
    this->m_anaios["dist_sensor"] = new AnalogInput(0);

    log_info("Registering Digital Inputs.");
    log_info("Adding DigitalInput ballDetector at ID=0");
    this->m_digios["ballDetector"] = new DigitalInput(0);

    log_info("Constructing RobotDrive");
    m_drive = new RobotDrive(
            this->m_talons["frontLeft"],this->m_talons["backLeft"],
            this->m_talons["frontRight"],this->m_talons["backRight"]);

    // NOTE: THIS MIGHT BE THE PROBLEM
    log_info("Setting default Servo values to 0.");
    this->m_servos["TESTSERVO"]->SetAngle(0);
    this->m_servos["WinchActivate"]->SetAngle(0);

    log_info("Starting Timer.");
    this->m_internal_timer->Start();

    log_info("Done Initializing HardwareManager.");
    return 0;
}

int HardwareManager::Update(){
    int ret = 0;

    /*
    if(this->m_digios["ballDetector"]->Get()){
        ret |= this->stop_suck();
    }
    */

    return ret;
}

bool HardwareManager::IsFinished(){
    return this->m_finished;
}

int HardwareManager::End(){
    return 0;
}

int HardwareManager::move(){
    this->m_drive->TankDrive(-m_joysticks[0]->GetAxis(2),-m_joysticks[1]->GetAxis(2));
    return 0;
}

int HardwareManager::move(float left,float right){
    // Reverse left
    this->m_drive->TankDrive(-left,right);
    return 0;
}

int HardwareManager::launch(){
    SmartDashboard::PutBoolean("Shooting",true);
    log_test("Launching..."); // pew pew
    this->m_servos["flap thing"]->SetAngle(180);
    return 0;
}

int HardwareManager::release(){
    SmartDashboard::PutBoolean("Releasing",true);
    this->m_talons["leftShoot"]->Set(0.4);
    this->m_talons["rightShoot"]->Set(-0.4);
    this->m_servos["flap thing"]->SetAngle(180);

    return 0;
}

int HardwareManager::init_climb(){
    this->m_servos["WinchActivate"]->SetAngle(180);
    return 0;
}

int HardwareManager::init_suck(){
    //this->m_servos["IntakeArmActivate"]->SetAngle(180);
    return 0;
}

int HardwareManager::uninit_suck(){
    //this->m_servos["IntakeArmActivate"]->SetAngle(0);
    return 0;
}

int HardwareManager::suck(){
    // TODO: Add pre-suck and post-suck stuff
    // Actually, is there anything it init and post init?
    SmartDashboard::PutBoolean("Sucking",true);
    this->m_talons["intake"]->Set(1);
    this->m_talons["leftShoot"]->Set(-0.6);
    this->m_talons["rightShoot"]->Set(0.6);

    return 0;
}

int HardwareManager::climb(){
    log_err("Somebody called climb(). This method is deprecated. Do not call it.");
    return 2;
}

int HardwareManager::move_arm(){
    log_err("Somebody called move_arm(). This method is deprecated. Do not call it.");
    return 0;
}

int HardwareManager::stop_suck(){
    SmartDashboard::PutBoolean("Sucking",false);
    this->m_talons["intake"]->Set(0);
    /*
    this->m_talons["leftShoot"]->Set(0);
    this->m_talons["rightShoot"]->Set(0);
    */
    return 0;
}

int HardwareManager::init_launch(){
    this->m_talons["leftShoot"]->Set(1.0);
    this->m_talons["rightShoot"]->Set(-1.0);
    return 0;
}

int HardwareManager::reset_launch(){
    SmartDashboard::PutBoolean("Shooting",false);
    this->m_talons["leftShoot"]->Set(0);
    this->m_talons["rightShoot"]->Set(0);
    this->m_servos["flap thing"]->SetAngle(0);
    return 0;
}

int HardwareManager::raise(){
    SmartDashboard::PutString("Arm Y: ","UP");
    log_test("ARM Y:UP");
    this->m_talons["armUpDown"]->Set(-0.3);
    return 0;
}

int HardwareManager::stop_raise(){
    this->m_talons["armUpDown"]->Set(0);
    return 0;
}

int HardwareManager::lower(){
    SmartDashboard::PutString("Arm Y: ","DOWN");
    log_test("ARM Y:DWN");
    this->m_talons["armUpDown"]->Set(0.3);
    return 0;
}

int HardwareManager::stop_lower(){
    this->m_talons["armUpDown"]->Set(0);
    return 0;
}

int HardwareManager::extend(){
    SmartDashboard::PutString("Arm Extend: ","FWD");
    log_test("ARM EXT:FWD");
    this->m_talons["armExtRet"]->Set(0.5);
    return 0;
}

int HardwareManager::stopExtRet(){
    this->m_talons["armExtRet"]->Set(0);
    return 0;
}

int HardwareManager::retract(){
    SmartDashboard::PutString("Arm Extend: ","REV");
    log_test("ARM EXT:REV");
    this->m_talons["armExtRet"]->Set(-0.5);
    return 0;
}

float HardwareManager::getDistanceSensorValue(){
    float val = this->m_anaios["dist_sensor"]->GetValue()*HardwareManager::DIST_SENSOR_CONST;
    // HOLY SHIT! WHY ON EARTH WOULD THIS VALUE BE LIKE THIS
    // WHAT DID YOU DO?!
    if(val >= 4.98){
        log_warn("Distance sensor is returning a value of 4.98 or higher.\nWhat the hell did you do?!\
                Don't worry, I'll set it to 4.98 just for you bby ;)");
        val = 4.98;
    }
    return val;
}

