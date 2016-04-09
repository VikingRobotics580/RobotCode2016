#include "HardwareManager.h"
#include "joystick.h"

const float HardwareManager::WHEEL_RPM_FULL_SPEED = 0.0;
const float HardwareManager::WHEEL_RADIUS = 0.0;
// What the hell is this constant Max?
const float HardwareManager::DIST_SENSOR_CONST = 0.0048828125;

HardwareManager::HardwareManager():
    BaseManager(),
    m_finished(false),
    m_talons(),
    m_servos(),
    m_anaios(),
    m_digios()
{
    m_drive = NULL;
    m_internal_timer = new Timer();
}

HardwareManager::~HardwareManager(){
}

int HardwareManager::Init(){
    log_info("Beginning HardwareManager Initialization.");

    // Initializes all CANTalons
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

    // Initializes all Talons
    log_info("Adding Talon leftShoot at ID=9");
    this->m_talons["leftShoot"] = new Talon(9);
    log_info("Adding Talon rightShoot at ID=8");
    this->m_talons["rightShoot"] = new Talon(8);
    log_info("Adding Talon armExtRet at ID=1");
    this->m_talons["armExtRet"] = new Talon(1);
    log_info("Adding Talon armUpDown at ID=3");
    this->m_talons["armUpDown"] = new Talon(3);

    // Sets all SpeedController objects to 0 to make sure they are all reset when the robot code restarts
    log_info("Setting all SpeedControllers to 0");
    for(talon_map::iterator it = m_talons.begin(); it != m_talons.end(); ++it){
        it->second->Set(0);
    }

    // Initializes all servos
    log_info("Adding Servo WinchActive at ID=5");
    this->m_servos["WinchActivate"] = new Servo(5);
    log_info("Adding Servo flap thing at ID=7");
    this->m_servos["flap thing"] = new Servo(7);

    // Initializes all sensors on the robot
    log_info("Registering Analog Channels.");
    log_info("Adding AnalogChannel dist_sensor at ID=0");
    this->m_anaios["dist_sensor"] = new AnalogInput(0);
    log_info("Registering Digital Inputs.");
    log_info("Adding DigitalInput ballDetector at ID=0");
    this->m_digios["ballDetector"] = new DigitalInput(0);

    // Constructs and Initializes RobotDrive
    // This object is used to control movement
    log_info("Constructing RobotDrive");
    m_drive = new RobotDrive(
            this->m_talons["frontLeft"],this->m_talons["backLeft"],
            this->m_talons["frontRight"],this->m_talons["backRight"]);

    log_info("Setting default Servo values to 0.");
    this->m_servos["flap thing"]->SetAngle(10); // This is set to 10, because we figured that 10 degrees is a better starting location that 0
    this->m_servos["WinchActivate"]->SetAngle(0);

    // Initializes an internal timer so that the rest of the code can know the time.
    // It's like Big Ben, if nobody else in London had a watch or any other sort of clock
    log_info("Starting Timer.");
    this->m_internal_timer->Start();

    log_info("Done Initializing HardwareManager.");
    return 0;
}

int HardwareManager::Update(){
    // We don't actually have anything to do here, so just do nothing successfully
    int ret = 0;

    return ret;
}

bool HardwareManager::IsFinished(){
    return this->m_finished;
}

int HardwareManager::End(){
    // Just like Update, we don't have anything we need to do here.
    return 0;
}

int HardwareManager::move(float left,float right){
    // Reverse left
    this->m_drive->TankDrive(-left,right); // Our robot uses a TankDrive system
    return 0;
}

int HardwareManager::launch(){
    SmartDashboard::PutBoolean("Shooting",true);
    log_test("Launching..."); // pew pew
    this->m_servos["flap thing"]->SetAngle(170);
    return 0;
}

int HardwareManager::release(){
    SmartDashboard::PutBoolean("Releasing",true);
    this->m_talons["leftShoot"]->Set(0.4);
    this->m_talons["rightShoot"]->Set(-0.4);
    this->m_servos["flap thing"]->SetAngle(180);
    this->m_talons["intake"]->Set(-1);

    return 0;
}

int HardwareManager::init_climb(){
    this->m_servos["WinchActivate"]->SetAngle(60);
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

int HardwareManager::stop_suck(){
    SmartDashboard::PutBoolean("Sucking",false);
    this->m_talons["intake"]->Set(0);
    return 0;
}

int HardwareManager::init_launch(){
    // Simply spins up the wheels in the shooting system
    this->m_talons["leftShoot"]->Set(1.0);
    this->m_talons["rightShoot"]->Set(-1.0);
    return 0;
}

int HardwareManager::reset_launch(){
    SmartDashboard::PutBoolean("Shooting",false);
    this->m_talons["leftShoot"]->Set(0);
    this->m_talons["rightShoot"]->Set(0);
    this->m_servos["flap thing"]->SetAngle(10);
    return 0;
}

int HardwareManager::raise(){
    SmartDashboard::PutString("Arm Y: ","UP");
    log_test("ARM Y:UP");
    this->m_talons["armUpDown"]->Set(-0.20);
    return 0;
}

int HardwareManager::stop_raise(){
    this->m_talons["armUpDown"]->Set(0);
    return 0;
}

int HardwareManager::lower(){
    SmartDashboard::PutString("Arm Y: ","DOWN");
    log_test("ARM Y:DWN");
    this->m_talons["armUpDown"]->Set(0.20);
    return 0;
}

int HardwareManager::stop_lower(){
    this->m_talons["armUpDown"]->Set(0);
    return 0;
}

int HardwareManager::extend(){
    SmartDashboard::PutString("Arm Extend: ","FWD");
    log_test("ARM EXT:FWD");
    this->m_talons["armExtRet"]->Set(-0.6); // Extend it at -60% power
    return 0;
}

int HardwareManager::stopExtRet(){
    this->m_talons["armExtRet"]->Set(0);
    return 0;
}

int HardwareManager::retract(){
    SmartDashboard::PutString("Arm Extend: ","REV");
    log_test("ARM EXT:REV");
    this->m_talons["armExtRet"]->Set(0.6);
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

