#pragma once


#include "elements/basic/air.h"
#include "elements/basic/burning_oil.h"
#include "elements/basic/cool_lava.h"
#include "elements/basic/explosion.h"
#include "elements/basic/explosive.h"
#include "elements/basic/fire.h"
#include "elements/basic/hurricane.h"
#include "elements/basic/ice.h"
#include "elements/basic/lava.h"
#include "elements/basic/lightning.h"
#include "elements/basic/lightning_flash.h"
#include "elements/basic/molten_glass.h"
#include "elements/basic/obsidian.h"
#include "elements/basic/oil.h"
#include "elements/basic/rock.h"
#include "elements/basic/salt_water.h"
#include "elements/basic/sand.h"
#include "elements/basic/smoke.h"
#include "elements/basic/snow.h"
#include "elements/basic/vapor.h"
#include "elements/basic/void.h"
#include "elements/basic/water.h"
#include "elements/build/crystal.h"
#include "elements/build/dust.h"
#include "elements/build/emerald.h"
#include "elements/build/glass.h"
#include "elements/build/lapis.h"
#include "elements/build/ruby.h"
#include "elements/build/salt.h"
#include "elements/build/sandstone.h"
#include "elements/build/soil.h"
#include "elements/build/wall.h"
#include "elements/build/wood.h"
#include "elements/build/info_cable.h"
#include "elements/build/info_cable_charged.h"
#include "elements/build/info_piston_down.h"
#include "elements/build/info_piston_up.h"
#include "elements/build/info_piston_down_charged.h"
#include "elements/build/info_piston_up_charged.h"
#include "elements/build/info_source.h"
#include "elements/build/info_deleter.h"
#include "elements/build/info_deleter_charged.h"
#include "elements/build/info_dust.h"
#include "elements/build/info_amplifier.h"
#include "elements/build/info_amplifier_charged.h"
#include "elements/chemical/acid.h"
#include "elements/chemical/acid_gas.h"
#include "elements/chemical/acid_water.h"
#include "elements/chemical/blue_fire.h"
#include "elements/chemical/burning_potassium.h"
#include "elements/chemical/carbon_dioxide.h"
#include "elements/chemical/cloud.h"
#include "elements/chemical/gold.h"
#include "elements/chemical/hydrogen.h"
#include "elements/chemical/hydrogen_explosion.h"
#include "elements/chemical/icework_a.h"
#include "elements/chemical/icework_b.h"
#include "elements/chemical/icework_c.h"
#include "elements/chemical/ice_bomb.h"
#include "elements/chemical/ice_dust.h"
#include "elements/chemical/ice_explosion.h"
#include "elements/chemical/iodine.h"
#include "elements/chemical/iodine_gas.h"
#include "elements/chemical/iodine_liquid.h"
#include "elements/chemical/iron.h"
#include "elements/chemical/mercury.h"
#include "elements/chemical/molten_gold.h"
#include "elements/chemical/nuclear_explosion.h"
#include "elements/chemical/osmium.h"
#include "elements/chemical/oxidized_potassium.h"
#include "elements/chemical/potassium.h"
#include "elements/chemical/potassium_explosion.h"
#include "elements/chemical/rust.h"
#include "elements/chemical/uranium.h"
#include "elements/chemical/dry_sponge.h"
#include "elements/chemical/wet_sponge.h"
#include "elements/life/algae_brown.h"
#include "elements/life/algae_green.h"
#include "elements/life/algae_red.h"
#include "elements/life/critter.h"
#include "elements/life/dragon.h"
#include "elements/life/fairy.h"
#include "elements/life/fish_left.h"
#include "elements/life/fish_right.h"
#include "elements/life/germ_seed.h"
#include "elements/life/grass.h"
#include "elements/life/nanobot.h"
#include "elements/life/penguin.h"
#include "elements/life/polliwog.h"
#include "elements/life/sandduck.h"
#include "elements/life/seed.h"
#include "elements/life/slime.h"
#include "elements/life/urchin.h"
#include "elements/life/virus.h"
#include "elements/space/beam.h"
#include "elements/space/black_hole.h"
#include "elements/space/firework_a.h"
#include "elements/space/firework_b.h"
#include "elements/space/firework_c.h"
#include "elements/space/firework_trail.h"
#include "elements/space/kuiper.h"
#include "elements/space/laser.h"
#include "elements/space/liquid_powder.h"
#include "elements/space/meteor_a.h"
#include "elements/space/meteor_b.h"
#include "elements/space/meteor_c.h"
#include "elements/space/neutron_beam.h"
#include "elements/space/plasma.h"
#include "elements/space/plasma_flash.h"
#include "elements/space/powder_a.h"
#include "elements/space/powder_b.h"
#include "elements/space/powder_c.h"
#include "elements/space/strange.h"
#include "elements/space/worm_hole.h"
#include "elements/space/beam_power.h"
#include "elements/space/beam_power_flash.h"
#include "elements/space/paradox.h"
#include "elements/space/glitch.h"
#include "elements/space/javelin_rain.h"
#include "elements/basic/white_sand.h"
#include "elements/life/blood.h"
#include "elements/life/algae_water.h"
#include "elements/life/flower_seed.h"
#include "elements/life/germ_flower_seed.h"
#include "elements/life/flower_stem.h"
#include "elements/life/flower_core.h"
#include "elements/life/flower_petal_a.h"
#include "elements/life/flower_petal_b.h"
#include "elements/life/flower_petal_c.h"
#include "elements/life/primordial_soup.h"
#include "elements/space/spiral.h"
#include "elements/life/turtle.h"
#include "elements/build/invisirock.h"
#include "elements/life/metal_slime.h"
#include "elements/custom_element.h"
#include "elements/chemical/silver.h"
#include "elements/chemical/molten_silver.h"
#include "elements/chemical/lead.h"
#include "elements/chemical/base.h"
#include "elements/space/draco_meteor_a.h"
#include "elements/space/draco_meteor_b.h"
#include "elements/space/draco_meteor_c.h"
#include "elements/space/firework_d.h"
#include "elements/space/firework_e.h"
#include "elements/space/firework_f.h"
#include "elements/space/firework_trail_d.h"
#include "elements/space/firework_trail_e.h"
#include "elements/space/firework_trail_f.h"
#include "elements/basic/tempest.h"
#include "elements/basic/tempest_up.h"
#include "elements/basic/mine.h"
#include "elements/basic/megido.h"
#include "elements/life/alien.h"
#include "elements/basic/sprinkles.h"
#include "elements/basic/quartz.h"
#include "elements/space/freeze_ray.h"
#include "elements/chemical/frozen_acid.h"
#include "elements/chemical/frozen_ammonia.h"
#include "elements/space/quick_sand.h"
#include "elements/space/rocket.h"
#include "elements/life/mutant.h"
#include "elements/basic/joy.h"
#include "elements/chemical/thermostat.h"
#include "elements/space/paraffin.h"
#include "elements/basic/peppermint.h"
#include "elements/basic/potion.h"
#include "elements/life/medusa.h"
#include "elements/space/stone_ray.h"
#include "elements/space/stone_trail.h"
#include "elements/life/black_slime.h"
#include "elements/life/mushroom_core.h"
#include "elements/life/mushroom_stem.h"
#include "elements/life/mushroom_shell_a.h"
#include "elements/life/mushroom_shell_b.h"
#include "elements/life/mushroom_shell_c.h"
#include "elements/basic/bedrock.h"
#include "elements/space/missile.h"
#include "elements/basic/glaggler_seed.h"
#include "elements/basic/glaggler_eye.h"
#include "elements/basic/glaggler_face.h"

class AllElements {
public:
    static void fill_elements(std::vector<Element*> *elements) {
        // Each element has a single object instance so that the program
        // can use polymorphism rather than explicitly stating which method
        // is called for each element type

        // The order in the vector is arbitrary, but it must match the list order in main.gd
        elements->resize(4097);
        elements->at(0) = new Void();
        elements->at(1) = new Sand();
        elements->at(2) = new Rock();
        elements->at(3) = new Water();
        elements->at(4) = new Polliwog();
        elements->at(5) = new Fire();
        elements->at(6) = new Smoke();
        elements->at(7) = new AlgaeGreen();
        elements->at(8) = new SandDuck();
        elements->at(9) = new Explosion();
        elements->at(10) = new Explosive();
        elements->at(11) = new Soil();
        elements->at(12) = new Seed();
        elements->at(13) = new GerminatedSeed();
        elements->at(14) = new Grass();
        elements->at(15) = new Wall();
        elements->at(16) = new Dust();
        elements->at(17) = new Iron();
        elements->at(18) = new Wood();
        elements->at(19) = new Ice();
        elements->at(20) = new Lava();
        elements->at(21) = new Acid();
        elements->at(22) = new AcidGas();
        elements->at(23) = new Fairy();
        elements->at(24) = new BlueFire();
        elements->at(25) = new Glass();
        elements->at(26) = new Laser();
        elements->at(27) = new Crystal();
        elements->at(28) = new Air();
        elements->at(29) = new BlackHole();
        elements->at(30) = new Oil();
        elements->at(31) = new Urchin();
        elements->at(32) = new Dragon();
        elements->at(33) = new Critter();
        elements->at(34) = new NuclearExplosion();
        elements->at(35) = new Uranium();
        elements->at(36) = new NeutronBeam();
        elements->at(37) = new Lightning();
        elements->at(38) = new LightningFlash();
        elements->at(39) = new Plasma();
        elements->at(40) = new PlasmaFlash();
        elements->at(41) = new Hurricane();
        elements->at(42) = new PowderA();
        elements->at(43) = new LiquidPowder();
        elements->at(44) = new Mercury();
        elements->at(45) = new Potassium();
        elements->at(46) = new PExplosion();
        elements->at(47) = new Hydrogen();
        elements->at(48) = new HydrogenExplosion();
        elements->at(49) = new Penguin();
        elements->at(50) = new BurningOil();
        elements->at(51) = new Gold();
        elements->at(52) = new MoltenGold();
        elements->at(53) = new MoltenGlass();
        elements->at(54) = new AlgaeRed();
        elements->at(55) = new AlgaeBrown();
        elements->at(56) = new CoolLava();
        elements->at(57) = new Obsidian();
        elements->at(58) = new Vapor();
        elements->at(59) = new AcidWater();
        elements->at(60) = new OxidizedPotassium();
        elements->at(61) = new BurningPotassium();
        elements->at(62) = new Rust();
        elements->at(63) = new PowderB();
        elements->at(64) = new PowderB();
        elements->at(65) = new Kuiper();
        elements->at(66) = new FireworkA();
        elements->at(67) = new FireworkB();
        elements->at(68) = new FireworkC();
        elements->at(69) = new FireworkTrail();
        elements->at(70) = new Salt();
        elements->at(71) = new SaltWater();
        elements->at(72) = new FishLeft();
        elements->at(73) = new FishRight();
        elements->at(74) = new Strange();
        elements->at(75) = new MeteorA();
        elements->at(76) = new MeteorB();
        elements->at(77) = new MeteorC();
        elements->at(78) = new Lapis();
        elements->at(79) = new Ruby();
        elements->at(80) = new Emerald();
        elements->at(81) = new WormHole();
        elements->at(82) = new Iodine();
        elements->at(83) = new IodineGas();
        elements->at(84) = new IodineLiquid();
        elements->at(85) = new Snow();
        elements->at(86) = new Slime();
        elements->at(87) = new Cloud();
        elements->at(88) = new IceExplosion();
        elements->at(89) = new IceDust();
        elements->at(90) = new IceworkA();
        elements->at(91) = new IceworkB();
        elements->at(92) = new IceworkC();
        elements->at(93) = new IceBomb();
        elements->at(94) = new Beam();
        elements->at(95) = new Nanobot();
        elements->at(96) = new CarbonDioxide();
        elements->at(97) = new Sandstone();
        elements->at(98) = new WhiteSand();
        elements->at(99) = new DrySponge();
        elements->at(100) = new WetSponge();
        elements->at(101) = new Virus();
        elements->at(102) = new InfoCable();
        elements->at(103) = new InfoCableCharged();
        elements->at(104) = new InfoSource();
        elements->at(105) = new InfoPistonDown();
        elements->at(106) = new InfoPistonUp();
        elements->at(107) = new InfoDeleter();
        elements->at(108) = new InfoDust();
        elements->at(109) = new InfoPistonDownCharged();
        elements->at(110) = new InfoPistonUpCharged();
        elements->at(111) = new InfoDeleterCharged();
        elements->at(112) = new InfoAmplifier();
        elements->at(113) = new InfoAmplifierCharged();
        elements->at(114) = new BeamPower();
        elements->at(115) = new BeamPowerFlash();
        elements->at(116) = new Paradox();
        elements->at(117) = new Glitch();
        elements->at(118) = new Blood();
        elements->at(119) = new FlowerSeed();
        elements->at(120) = new GerminatedFlowerSeed();
        elements->at(121) = new FlowerStem();
        elements->at(122) = new FlowerCore();
        elements->at(123) = new FlowerPetalA();
        elements->at(124) = new FlowerPetalB();
        elements->at(125) = new FlowerPetalC();
        elements->at(126) = new AlgaeWater();
        elements->at(127) = new PrimordialSoup();
        elements->at(128) = new JavelinRain();
        elements->at(129) = new Spiral();
        elements->at(130) = new Turtle();
        elements->at(131) = new Invisirock();
        elements->at(132) = new MetalSlime();
        elements->at(133) = new Silver();
        elements->at(134) = new MoltenSilver();
        elements->at(135) = new Lead();
        elements->at(136) = new Base();
        elements->at(137) = new DracoMeteorA();
        elements->at(138) = new DracoMeteorB();
        elements->at(139) = new DracoMeteorC();
        elements->at(140) = new FireworkD();
        elements->at(141) = new FireworkE();
        elements->at(142) = new FireworkF();
        elements->at(143) = new FireworkTrailD();
        elements->at(144) = new FireworkTrailE();
        elements->at(145) = new FireworkTrailF();
        elements->at(146) = new Tempest();
        elements->at(147) = new TempestUp();
        elements->at(148) = new Mine();
        elements->at(149) = new Megido();
        elements->at(150) = new Alien();
        elements->at(151) = new Sprinkles();
        elements->at(152) = new Quartz();
        elements->at(153) = new FreezeRay();
        elements->at(154) = new FrozenAcid();
        elements->at(155) = new FrozenAmmonia();
        elements->at(156) = new QuickSand();
        elements->at(157) = new Rocket();
        elements->at(158) = new Mutant();
        elements->at(159) = new Joy();
        elements->at(160) = new Thermostat();
        elements->at(161) = new Paraffin();
        elements->at(162) = new Mint();
        elements->at(163) = new Potion();
        elements->at(164) = new Medusa();
        elements->at(165) = new StoneRay();
        elements->at(166) = new StoneTrail();
        elements->at(167) = new BlackSlime();
        elements->at(168) = new MushroomCore();
        elements->at(169) = new MushroomStem();
        elements->at(170) = new MushroomShellA();
        elements->at(171) = new MushroomShellB();
        elements->at(172) = new MushroomShellC();
        elements->at(173) = new Bedrock();
        elements->at(174) = new Missile();
        elements->at(175) = new GlagglerSeed();
        elements->at(176) = new GlagglerEye();
        elements->at(177) = new GlagglerFace();


        for (int i = 2048; i <= 4096; i++) {
            elements->at(i) = new CustomElementParticle();
        }
    }
};

