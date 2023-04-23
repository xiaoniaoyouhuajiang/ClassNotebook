#-------------------------------------------------
#
# Project created by QtCreator 2020-03-14T20:15:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OOP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    AffectBehavior/AffectBehavior.cpp \
    AffectBehavior/LargeArmorAffectBehavior.cpp \
    AffectBehavior/LargeMedicineAffectBehavior.cpp \
    AffectBehavior/SmallArmorAffectBehavior.cpp \
    AffectBehavior/SmallMedicineAffectBehavior.cpp \
    AffectBehavior/SmallMedicineBehavior.cpp \
    Armor/Armor.cpp \
    Armor/HeavyArmor.cpp \
    Armor/LiteArmor.cpp \
    Armor/MediumArmor.cpp \
    Armor/NoArmor.cpp \
    AttackBehavior/AttackBehavior.cpp \
    AttackBehavior/AttackWithBat.cpp \
    AttackBehavior/BikeAttack.cpp \
    AttackBehavior/BlowingUpAttackBehavior.cpp \
    AttackBehavior/CarAttack.cpp \
    AttackBehavior/GrenadeAttack.cpp \
    AttackBehavior/GunAttack.cpp \
    AttackBehavior/SpitToAreaAttack.cpp \
    AttackBehavior/SpitToEnemyAttack.cpp \
    AttackBehavior/StinkyAttack.cpp \
    AttackBehavior/StrongNearAttack.cpp \
    AttackBehavior/SwordAttack.cpp \
    Commands/AttackCommand.cpp \
    Commands/Command.cpp \
    Commands/CreateUnitCommand.cpp \
    Commands/MoveCommand.cpp \
    Commands/SetTowerCommand.cpp \
    Control/Facade.cpp \
    Control/Mediator.cpp \
    Fabrics/BitingZombyFactory.cpp \
    Fabrics/HumanOnBikeFactory.cpp \
    Fabrics/HumanOnCarFactory.cpp \
    Fabrics/HumanWithBatFactory.cpp \
    Fabrics/HumanWithGrenadeFactory.cpp \
    Fabrics/HumanWithGunFactory.cpp \
    Fabrics/HumanWithSwordFactory.cpp \
    Fabrics/KamikadzeZombyFactory.cpp \
    Fabrics/SpitToAreaZombyFactory.cpp \
    Fabrics/SpitToEnemyZombyFactory.cpp \
    Fabrics/StinkyZombyFactory.cpp \
    Fabrics/StrongZombyFactory.cpp \
    Fabrics/UnitFactory.cpp \
    Field/Field.cpp \
    Field/FieldCell.cpp \
    Handlers/FinalAttackHandler.cpp \
    Handlers/FinalCreateUnitHandler.cpp \
    Handlers/FinalMoveHandler.cpp \
    Handlers/FinalSetTowerHandler.cpp \
    Handlers/freeCellForTowerHandler.cpp \
    Handlers/FreeCellForUnitHandler.cpp \
    Handlers/Handler.cpp \
    Handlers/TowerExistenceHandler.cpp \
    Handlers/TowerPosibilityHandler.cpp \
    Handlers/UnitExistenceHandler.cpp \
    Land/CommonLand.cpp \
    Land/GrassLand.cpp \
    Land/HillLand.cpp \
    Land/Land.cpp \
    Land/LandInterface.cpp \
    Land/ProxyLand.cpp \
    Loger/ConsoleLoger.cpp \
    Loger/FileLoger.cpp \
    Loger/Loger.cpp \
    Loger/LogerAdapter.cpp \
    Loger/LogerProxy.cpp \
    Loger/LogInterface.cpp \
    Messages/EndStepMessage.cpp \
    Messages/HandlerEngagedCellMessage.cpp \
    Messages/HandlerNotExistMessage.cpp \
    Messages/HandlerTowerNotExistMessage.cpp \
    Messages/HandlerTowerPossibilityMessage.cpp \
    Messages/Message.cpp \
    Messages/TowerCreateMessage.cpp \
    Messages/TowerDamageMessage.cpp \
    Messages/TowerDeathMessage.cpp \
    Messages/TowerStatusMessage.cpp \
    Messages/UnitAttackMessage.cpp \
    Messages/UnitCreateMessage.cpp \
    Messages/UnitDeathMessage.cpp \
    Messages/UnitGetDamageMessage.cpp \
    Messages/UnitMoveMessage.cpp \
    Messages/UnitStatusMessage.cpp \
    Messages/UserAttackMessage.cpp \
    Messages/UserCreateUnitMessage.cpp \
    Messages/UserMoveMessage.cpp \
    Messages/UserSetTowerMessage.cpp \
    MoveBehavior/BikeMove.cpp \
    MoveBehavior/CarMove.cpp \
    MoveBehavior/CommonHumanMove.cpp \
    MoveBehavior/CommonMove.cpp \
    MoveBehavior/FatZombyMoveBehavior.cpp \
    MoveBehavior/MoveBehavior.cpp \
    NeutralObject/ArmorObject.cpp \
    NeutralObject/LargeArmorObject.cpp \
    NeutralObject/LargeMedicine.cpp \
    NeutralObject/MedicineObject.cpp \
    NeutralObject/NeutralObject.cpp \
    NeutralObject/NeutralObjectInterface.cpp \
    NeutralObject/SmallArmorObject.cpp \
    NeutralObject/SmallMedicine.cpp \
    Observer/ObserverInterface.cpp \
    Observer/SubjectInterface.cpp \
    Tower/Tower.cpp \
    Units/BitingZomby.cpp \
    Units/CommonZomby.cpp \
    Units/FatZomby.cpp \
    Units/Human.cpp \
    Units/HumanOnBike.cpp \
    Units/HumanOnCar.cpp \
    Units/HumanOnMachine.cpp \
    Units/HumanWithBat.cpp \
    Units/HumanWithGrenade.cpp \
    Units/HumanWithGun.cpp \
    Units/HumanWithSword.cpp \
    Units/KamikadzeZomby.cpp \
    Units/MeleeHuman.cpp \
    Units/RangeHuman.cpp \
    Units/SpitToAreaZomby.cpp \
    Units/SpitToEnemyZomby.cpp \
    Units/SpitZomby.cpp \
    Units/StinkyZomby.cpp \
    Units/StrongZomby.cpp \
    Units/Unit.cpp \
    Units/UnitInterface.cpp \
    Units/ZombyUnit.cpp \
    Weapon/Bat.cpp \
    Weapon/BitingHead.cpp \
    Weapon/BlowingUpHead.cpp \
    Weapon/Grenade.cpp \
    Weapon/NoWeapon.cpp \
    Weapon/Pistol.cpp \
    Weapon/SpittingToAreaHead.cpp \
    Weapon/SpittingToEnemyHead.cpp \
    Weapon/StinkingBody.cpp \
    Weapon/StrongArm.cpp \
    Weapon/Sword.cpp \
    Weapon/Weapon.cpp \
    Save/Loader.cpp \
    Save/ObjectSnapshot.cpp \
    Save/Saver.cpp \
    Save/TowerSnapshot.cpp \
    Save/UnitSnapshot.cpp \
    gamewindow.cpp \
    Game/towersettingstate.cpp \
    Game/state.cpp \
    Game/unitsettingstate.cpp \
    paintwidget.cpp \
    AttackBehavior/BiteAttack.cpp \
    Fabrics/NeutralObjectFactory.cpp \
    Game/SignalMaker.cpp \
    Game/SingleGame.cpp



HEADERS += \
        mainwindow.h \
    AffectBehavior/AffectBehavior.h \
    AffectBehavior/LargeArmorAffectBehavior.h \
    AffectBehavior/LargeMedicineAffectBehavior.h \
    AffectBehavior/SmallArmorAffectBehavior.h \
    AffectBehavior/SmallMedicineAffectBehavior.h \
    AffectBehavior/SmallMedicineBehavior.h \
    Armor/Armor.h \
    Armor/HeavyArmor.h \
    Armor/LiteArmor.h \
    Armor/MediumArmor.h \
    Armor/NoArmor.h \
    AttackBehavior/AttackBehavior.h \
    AttackBehavior/AttackWithBat.h \
    AttackBehavior/BikeAttack.h \
    AttackBehavior/BlowingUpAttackBehavior.h \
    AttackBehavior/CarAttack.h \
    AttackBehavior/GrenadeAttack.h \
    AttackBehavior/GunAttack.h \
    AttackBehavior/SpitToAreaAttack.h \
    AttackBehavior/SpitToEnemyAttack.h \
    AttackBehavior/StinkyAttack.h \
    AttackBehavior/StrongNearAttack.h \
    AttackBehavior/SwordAttack.h \
    Commands/AttackCommand.h \
    Commands/Command.h \
    Commands/CreateUnitCommand.h \
    Commands/MoveCommand.h \
    Commands/SetTowerCommand.h \
    Control/Facade.h \
    Control/Mediator.h \
    Fabrics/BitingZombyFactory.h \
    Fabrics/HumanOnBikeFactory.h \
    Fabrics/HumanOnCarFactory.h \
    Fabrics/HumanWithBatFactory.h \
    Fabrics/HumanWithGrenadeFactory.h \
    Fabrics/HumanWithGunFactory.h \
    Fabrics/HumanWithSwordFactory.h \
    Fabrics/KamikadzeZombyFactory.h \
    Fabrics/SpitToAreaZombyFactory.h \
    Fabrics/SpitToEnemyZombyFactory.h \
    Fabrics/StinkyZombyFactory.h \
    Fabrics/StrongZombyFactory.h \
    Fabrics/UnitFactory.h \
    Field/Field.h \
    Field/FieldCell.h \
    Handlers/FinalAttackHandler.h \
    Handlers/FinalCreateUnitHandler.h \
    Handlers/FinalMoveHandler.h \
    Handlers/FinalSetTowerHandler.h \
    Handlers/freeCellForTowerHandler.h \
    Handlers/FreeCellForUnitHandler.h \
    Handlers/Handler.h \
    Handlers/TowerExistenceHandler.h \
    Handlers/TowerPosibilityHandler.h \
    Handlers/UnitExistenceHandler.h \
    Land/CommonLand.h \
    Land/GrassLand.h \
    Land/HillLand.h \
    Land/Land.h \
    Land/LandInterface.h \
    Land/ProxyLand.h \
    Loger/ConsoleLoger.h \
    Loger/FileLoger.h \
    Loger/Loger.h \
    Loger/LogerAdapter.h \
    Loger/LogerProxy.h \
    Loger/LogInterface.h \
    Messages/EndStepMessage.h \
    Messages/HandlerEngagedCellMessage.h \
    Messages/HandlerNotExistMessage.h \
    Messages/HandlerTowerNotExistMessage.h \
    Messages/HandlerTowerPossibilityMessage.h \
    Messages/Message.h \
    Messages/TowerCreateMessage.h \
    Messages/TowerDamageMessage.h \
    Messages/TowerDeathMessage.h \
    Messages/TowerStatusMessage.h \
    Messages/UnitAttackMessage.h \
    Messages/UnitCreateMessage.h \
    Messages/UnitDeathMessage.h \
    Messages/UnitGetDamageMessage.h \
    Messages/UnitMoveMessage.h \
    Messages/UnitStatusMessage.h \
    Messages/UserAttackMessage.h \
    Messages/UserCreateUnitMessage.h \
    Messages/UserMoveMessage.h \
    Messages/UserSetTowerMessage.h \
    MoveBehavior/BikeMove.h \
    MoveBehavior/CarMove.h \
    MoveBehavior/CommonHumanMove.h \
    MoveBehavior/CommonMove.h \
    MoveBehavior/FatZombyMoveBehavior.h \
    MoveBehavior/MoveBehavior.h \
    NeutralObject/ArmorObject.h \
    NeutralObject/LargeArmorObject.h \
    NeutralObject/LargeMedicine.h \
    NeutralObject/MedicineObject.h \
    NeutralObject/NeutralObject.h \
    NeutralObject/NeutralObjectInterface.h \
    NeutralObject/SmallArmorObject.h \
    NeutralObject/SmallMedicine.h \
    Observer/ObserverInterface.h \
    Observer/SubjectInterface.h \
    Structures/Kind.h \
    Structures/Point.h \
    Structures/Request.h \
    Structures/resource.h \
    Tower/Tower.h \
    Units/BitingZomby.h \
    Units/CommonZomby.h \
    Units/FatZomby.h \
    Units/Human.h \
    Units/HumanOnBike.h \
    Units/HumanOnCar.h \
    Units/HumanOnMachine.h \
    Units/HumanWithBat.h \
    Units/HumanWithGrenade.h \
    Units/HumanWithGun.h \
    Units/HumanWithSword.h \
    Units/KamikadzeZomby.h \
    Units/MeleeHuman.h \
    Units/RangeHuman.h \
    Units/SpitToAreaZomby.h \
    Units/SpitToEnemyZomby.h \
    Units/SpitZomby.h \
    Units/StinkyZomby.h \
    Units/StrongZomby.h \
    Units/Unit.h \
    Units/UnitInterface.h \
    Units/ZombyUnit.h \
    Weapon/Bat.h \
    Weapon/BitingHead.h \
    Weapon/BlowingUpHead.h \
    Weapon/Grenade.h \
    Weapon/NoWeapon.h \
    Weapon/Pistol.h \
    Weapon/SpittingToAreaHead.h \
    Weapon/SpittingToEnemyHead.h \
    Weapon/StinkingBody.h \
    Weapon/StrongArm.h \
    Weapon/Sword.h \
    Weapon/Weapon.h \
    Save/Loader.h \
    Save/ObjectSnapshot.h \
    Save/Saver.h \
    Save/TowerSnapshot.h \
    Save/UnitSnapshot.h \
    Units/UnitType.h \
    gamewindow.h \
    Game/Game.h \
    Game/gameinterface.h \
    Game/towersettingstate.h \
    Game/state.h \
    Game/unitsettingstate.h \
    Game/twoplayersgame.h \
    Game/twoplayersrule.h \
    paintwidget.h \
    AttackBehavior/BiteAttack.h \
    Fabrics/NeutralObjectFactory.h \
    Game/SignalMaker.h \
    Game/gamemode.h \
    Game/statetype.h \
    Game/SingleGame.h



FORMS += \
        mainwindow.ui


INCLUDEPATH += \
    AffectBehavior \
    Armor \
    AttackBehavior \
    Commands \
    Control \
    Fabrics \
    Field \
    Game \
    Handlers \
    Land \
    Loger \
    Messages \
    MoveBehavior \
    NeutralObject \
    Observer \
    Save \
    Structures \
    Tower \
    Units \
    Weapon \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
