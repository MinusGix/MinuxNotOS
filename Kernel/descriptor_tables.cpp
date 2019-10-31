#include "descriptor_tables.hpp"
#include "memory.hpp"
#include "io.hpp"
#include "isr.hpp"

GDT::Entry gdt_entries[5];
GDT::Pointer gdt_ptr;
IDT::Entry idt_entries[256];
IDT::Pointer idt_ptr;

void init_descriptor_tables () {
    GDT::init();
    IDT::init();
}

void GDT::init () {
    gdt_ptr.limit = (sizeof(GDT::Entry) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    GDT::setGate(0, 0, 0,          0,    0);    // Null segment
    GDT::setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    GDT::setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    GDT::setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    GDT::setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    GDT::flush((uint32_t)&gdt_ptr);
}

void GDT::flush (uint32_t gdt_pointer) {
    return GDT::detail::gdt_flush(gdt_pointer);
}

void IDT::init () {
    idt_ptr.limit = sizeof(IDT::Entry) * 256 -1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    Memory::memset(&idt_entries, 0, sizeof(IDT::Entry)*256);

    IDT::setGate(0, (uint32_t)ISR::isr0, 0x08, 0x8E);
    IDT::setGate(1, (uint32_t)ISR::isr1, 0x08, 0x8E);
    IDT::setGate(2, (uint32_t)ISR::isr2, 0x08, 0x8E);
    IDT::setGate(3, (uint32_t)ISR::isr3, 0x08, 0x8E);
    IDT::setGate(4, (uint32_t)ISR::isr4, 0x08, 0x8E);
    IDT::setGate(5, (uint32_t)ISR::isr5, 0x08, 0x8E);
    IDT::setGate(6, (uint32_t)ISR::isr6, 0x08, 0x8E);
    IDT::setGate(7, (uint32_t)ISR::isr7, 0x08, 0x8E);
    IDT::setGate(8, (uint32_t)ISR::isr8, 0x08, 0x8E);
    IDT::setGate(9, (uint32_t)ISR::isr9, 0x08, 0x8E);
    IDT::setGate(10, (uint32_t)ISR::isr10, 0x08, 0x8E);
    IDT::setGate(11, (uint32_t)ISR::isr11, 0x08, 0x8E);
    IDT::setGate(12, (uint32_t)ISR::isr12, 0x08, 0x8E);
    IDT::setGate(13, (uint32_t)ISR::isr13, 0x08, 0x8E);
    IDT::setGate(14, (uint32_t)ISR::isr14, 0x08, 0x8E);
    IDT::setGate(15, (uint32_t)ISR::isr15, 0x08, 0x8E);
    IDT::setGate(16, (uint32_t)ISR::isr16, 0x08, 0x8E);
    IDT::setGate(17, (uint32_t)ISR::isr17, 0x08, 0x8E);
    IDT::setGate(18, (uint32_t)ISR::isr18, 0x08, 0x8E);
    IDT::setGate(19, (uint32_t)ISR::isr19, 0x08, 0x8E);
    IDT::setGate(20, (uint32_t)ISR::isr20, 0x08, 0x8E);
    IDT::setGate(21, (uint32_t)ISR::isr21, 0x08, 0x8E);
    IDT::setGate(22, (uint32_t)ISR::isr22, 0x08, 0x8E);
    IDT::setGate(23, (uint32_t)ISR::isr23, 0x08, 0x8E);
    IDT::setGate(24, (uint32_t)ISR::isr24, 0x08, 0x8E);
    IDT::setGate(25, (uint32_t)ISR::isr25, 0x08, 0x8E);
    IDT::setGate(26, (uint32_t)ISR::isr26, 0x08, 0x8E);
    IDT::setGate(27, (uint32_t)ISR::isr27, 0x08, 0x8E);
    IDT::setGate(28, (uint32_t)ISR::isr28, 0x08, 0x8E);
    IDT::setGate(29, (uint32_t)ISR::isr29, 0x08, 0x8E);
    IDT::setGate(30, (uint32_t)ISR::isr30, 0x08, 0x8E);
    IDT::setGate(31, (uint32_t)ISR::isr31, 0x08, 0x8E);
    IDT::setGate(32, (uint32_t)ISR::isr32, 0x08, 0x8E);
    IDT::setGate(33, (uint32_t)ISR::isr33, 0x08, 0x8E);
    IDT::setGate(34, (uint32_t)ISR::isr34, 0x08, 0x8E);
    IDT::setGate(35, (uint32_t)ISR::isr35, 0x08, 0x8E);
    IDT::setGate(36, (uint32_t)ISR::isr36, 0x08, 0x8E);
    IDT::setGate(37, (uint32_t)ISR::isr37, 0x08, 0x8E);
    IDT::setGate(38, (uint32_t)ISR::isr38, 0x08, 0x8E);
    IDT::setGate(39, (uint32_t)ISR::isr39, 0x08, 0x8E);
    IDT::setGate(40, (uint32_t)ISR::isr40, 0x08, 0x8E);
    IDT::setGate(41, (uint32_t)ISR::isr41, 0x08, 0x8E);
    IDT::setGate(42, (uint32_t)ISR::isr42, 0x08, 0x8E);
    IDT::setGate(43, (uint32_t)ISR::isr43, 0x08, 0x8E);
    IDT::setGate(44, (uint32_t)ISR::isr44, 0x08, 0x8E);
    IDT::setGate(45, (uint32_t)ISR::isr45, 0x08, 0x8E);
    IDT::setGate(46, (uint32_t)ISR::isr46, 0x08, 0x8E);
    IDT::setGate(47, (uint32_t)ISR::isr47, 0x08, 0x8E);
    IDT::setGate(48, (uint32_t)ISR::isr48, 0x08, 0x8E);
    IDT::setGate(49, (uint32_t)ISR::isr49, 0x08, 0x8E);
    IDT::setGate(50, (uint32_t)ISR::isr50, 0x08, 0x8E);
    IDT::setGate(51, (uint32_t)ISR::isr51, 0x08, 0x8E);
    IDT::setGate(52, (uint32_t)ISR::isr52, 0x08, 0x8E);
    IDT::setGate(53, (uint32_t)ISR::isr53, 0x08, 0x8E);
    IDT::setGate(54, (uint32_t)ISR::isr54, 0x08, 0x8E);
    IDT::setGate(55, (uint32_t)ISR::isr55, 0x08, 0x8E);
    IDT::setGate(56, (uint32_t)ISR::isr56, 0x08, 0x8E);
    IDT::setGate(57, (uint32_t)ISR::isr57, 0x08, 0x8E);
    IDT::setGate(58, (uint32_t)ISR::isr58, 0x08, 0x8E);
    IDT::setGate(59, (uint32_t)ISR::isr59, 0x08, 0x8E);
    IDT::setGate(60, (uint32_t)ISR::isr60, 0x08, 0x8E);
    IDT::setGate(61, (uint32_t)ISR::isr61, 0x08, 0x8E);
    IDT::setGate(62, (uint32_t)ISR::isr62, 0x08, 0x8E);
    IDT::setGate(63, (uint32_t)ISR::isr63, 0x08, 0x8E);
    IDT::setGate(64, (uint32_t)ISR::isr64, 0x08, 0x8E);
    IDT::setGate(65, (uint32_t)ISR::isr65, 0x08, 0x8E);
    IDT::setGate(66, (uint32_t)ISR::isr66, 0x08, 0x8E);
    IDT::setGate(67, (uint32_t)ISR::isr67, 0x08, 0x8E);
    IDT::setGate(68, (uint32_t)ISR::isr68, 0x08, 0x8E);
    IDT::setGate(69, (uint32_t)ISR::isr69, 0x08, 0x8E);
    IDT::setGate(70, (uint32_t)ISR::isr70, 0x08, 0x8E);
    IDT::setGate(71, (uint32_t)ISR::isr71, 0x08, 0x8E);
    IDT::setGate(72, (uint32_t)ISR::isr72, 0x08, 0x8E);
    IDT::setGate(73, (uint32_t)ISR::isr73, 0x08, 0x8E);
    IDT::setGate(74, (uint32_t)ISR::isr74, 0x08, 0x8E);
    IDT::setGate(75, (uint32_t)ISR::isr75, 0x08, 0x8E);
    IDT::setGate(76, (uint32_t)ISR::isr76, 0x08, 0x8E);
    IDT::setGate(77, (uint32_t)ISR::isr77, 0x08, 0x8E);
    IDT::setGate(78, (uint32_t)ISR::isr78, 0x08, 0x8E);
    IDT::setGate(79, (uint32_t)ISR::isr79, 0x08, 0x8E);
    IDT::setGate(80, (uint32_t)ISR::isr80, 0x08, 0x8E);
    IDT::setGate(81, (uint32_t)ISR::isr81, 0x08, 0x8E);
    IDT::setGate(82, (uint32_t)ISR::isr82, 0x08, 0x8E);
    IDT::setGate(83, (uint32_t)ISR::isr83, 0x08, 0x8E);
    IDT::setGate(84, (uint32_t)ISR::isr84, 0x08, 0x8E);
    IDT::setGate(85, (uint32_t)ISR::isr85, 0x08, 0x8E);
    IDT::setGate(86, (uint32_t)ISR::isr86, 0x08, 0x8E);
    IDT::setGate(87, (uint32_t)ISR::isr87, 0x08, 0x8E);
    IDT::setGate(88, (uint32_t)ISR::isr88, 0x08, 0x8E);
    IDT::setGate(89, (uint32_t)ISR::isr89, 0x08, 0x8E);
    IDT::setGate(90, (uint32_t)ISR::isr90, 0x08, 0x8E);
    IDT::setGate(91, (uint32_t)ISR::isr91, 0x08, 0x8E);
    IDT::setGate(92, (uint32_t)ISR::isr92, 0x08, 0x8E);
    IDT::setGate(93, (uint32_t)ISR::isr93, 0x08, 0x8E);
    IDT::setGate(94, (uint32_t)ISR::isr94, 0x08, 0x8E);
    IDT::setGate(95, (uint32_t)ISR::isr95, 0x08, 0x8E);
    IDT::setGate(96, (uint32_t)ISR::isr96, 0x08, 0x8E);
    IDT::setGate(97, (uint32_t)ISR::isr97, 0x08, 0x8E);
    IDT::setGate(98, (uint32_t)ISR::isr98, 0x08, 0x8E);
    IDT::setGate(99, (uint32_t)ISR::isr99, 0x08, 0x8E);
    IDT::setGate(100, (uint32_t)ISR::isr100, 0x08, 0x8E);
    IDT::setGate(101, (uint32_t)ISR::isr101, 0x08, 0x8E);
    IDT::setGate(102, (uint32_t)ISR::isr102, 0x08, 0x8E);
    IDT::setGate(103, (uint32_t)ISR::isr103, 0x08, 0x8E);
    IDT::setGate(104, (uint32_t)ISR::isr104, 0x08, 0x8E);
    IDT::setGate(105, (uint32_t)ISR::isr105, 0x08, 0x8E);
    IDT::setGate(106, (uint32_t)ISR::isr106, 0x08, 0x8E);
    IDT::setGate(107, (uint32_t)ISR::isr107, 0x08, 0x8E);
    IDT::setGate(108, (uint32_t)ISR::isr108, 0x08, 0x8E);
    IDT::setGate(109, (uint32_t)ISR::isr109, 0x08, 0x8E);
    IDT::setGate(110, (uint32_t)ISR::isr110, 0x08, 0x8E);
    IDT::setGate(111, (uint32_t)ISR::isr111, 0x08, 0x8E);
    IDT::setGate(112, (uint32_t)ISR::isr112, 0x08, 0x8E);
    IDT::setGate(113, (uint32_t)ISR::isr113, 0x08, 0x8E);
    IDT::setGate(114, (uint32_t)ISR::isr114, 0x08, 0x8E);
    IDT::setGate(115, (uint32_t)ISR::isr115, 0x08, 0x8E);
    IDT::setGate(116, (uint32_t)ISR::isr116, 0x08, 0x8E);
    IDT::setGate(117, (uint32_t)ISR::isr117, 0x08, 0x8E);
    IDT::setGate(118, (uint32_t)ISR::isr118, 0x08, 0x8E);
    IDT::setGate(119, (uint32_t)ISR::isr119, 0x08, 0x8E);
    IDT::setGate(120, (uint32_t)ISR::isr120, 0x08, 0x8E);
    IDT::setGate(121, (uint32_t)ISR::isr121, 0x08, 0x8E);
    IDT::setGate(122, (uint32_t)ISR::isr122, 0x08, 0x8E);
    IDT::setGate(123, (uint32_t)ISR::isr123, 0x08, 0x8E);
    IDT::setGate(124, (uint32_t)ISR::isr124, 0x08, 0x8E);
    IDT::setGate(125, (uint32_t)ISR::isr125, 0x08, 0x8E);
    IDT::setGate(126, (uint32_t)ISR::isr126, 0x08, 0x8E);
    IDT::setGate(127, (uint32_t)ISR::isr127, 0x08, 0x8E);
    IDT::setGate(128, (uint32_t)ISR::isr128, 0x08, 0x8E);
    IDT::setGate(129, (uint32_t)ISR::isr129, 0x08, 0x8E);
    IDT::setGate(130, (uint32_t)ISR::isr130, 0x08, 0x8E);
    IDT::setGate(131, (uint32_t)ISR::isr131, 0x08, 0x8E);
    IDT::setGate(132, (uint32_t)ISR::isr132, 0x08, 0x8E);
    IDT::setGate(133, (uint32_t)ISR::isr133, 0x08, 0x8E);
    IDT::setGate(134, (uint32_t)ISR::isr134, 0x08, 0x8E);
    IDT::setGate(135, (uint32_t)ISR::isr135, 0x08, 0x8E);
    IDT::setGate(136, (uint32_t)ISR::isr136, 0x08, 0x8E);
    IDT::setGate(137, (uint32_t)ISR::isr137, 0x08, 0x8E);
    IDT::setGate(138, (uint32_t)ISR::isr138, 0x08, 0x8E);
    IDT::setGate(139, (uint32_t)ISR::isr139, 0x08, 0x8E);
    IDT::setGate(140, (uint32_t)ISR::isr140, 0x08, 0x8E);
    IDT::setGate(141, (uint32_t)ISR::isr141, 0x08, 0x8E);
    IDT::setGate(142, (uint32_t)ISR::isr142, 0x08, 0x8E);
    IDT::setGate(143, (uint32_t)ISR::isr143, 0x08, 0x8E);
    IDT::setGate(144, (uint32_t)ISR::isr144, 0x08, 0x8E);
    IDT::setGate(145, (uint32_t)ISR::isr145, 0x08, 0x8E);
    IDT::setGate(146, (uint32_t)ISR::isr146, 0x08, 0x8E);
    IDT::setGate(147, (uint32_t)ISR::isr147, 0x08, 0x8E);
    IDT::setGate(148, (uint32_t)ISR::isr148, 0x08, 0x8E);
    IDT::setGate(149, (uint32_t)ISR::isr149, 0x08, 0x8E);
    IDT::setGate(150, (uint32_t)ISR::isr150, 0x08, 0x8E);
    IDT::setGate(151, (uint32_t)ISR::isr151, 0x08, 0x8E);
    IDT::setGate(152, (uint32_t)ISR::isr152, 0x08, 0x8E);
    IDT::setGate(153, (uint32_t)ISR::isr153, 0x08, 0x8E);
    IDT::setGate(154, (uint32_t)ISR::isr154, 0x08, 0x8E);
    IDT::setGate(155, (uint32_t)ISR::isr155, 0x08, 0x8E);
    IDT::setGate(156, (uint32_t)ISR::isr156, 0x08, 0x8E);
    IDT::setGate(157, (uint32_t)ISR::isr157, 0x08, 0x8E);
    IDT::setGate(158, (uint32_t)ISR::isr158, 0x08, 0x8E);
    IDT::setGate(159, (uint32_t)ISR::isr159, 0x08, 0x8E);
    IDT::setGate(160, (uint32_t)ISR::isr160, 0x08, 0x8E);
    IDT::setGate(161, (uint32_t)ISR::isr161, 0x08, 0x8E);
    IDT::setGate(162, (uint32_t)ISR::isr162, 0x08, 0x8E);
    IDT::setGate(163, (uint32_t)ISR::isr163, 0x08, 0x8E);
    IDT::setGate(164, (uint32_t)ISR::isr164, 0x08, 0x8E);
    IDT::setGate(165, (uint32_t)ISR::isr165, 0x08, 0x8E);
    IDT::setGate(166, (uint32_t)ISR::isr166, 0x08, 0x8E);
    IDT::setGate(167, (uint32_t)ISR::isr167, 0x08, 0x8E);
    IDT::setGate(168, (uint32_t)ISR::isr168, 0x08, 0x8E);
    IDT::setGate(169, (uint32_t)ISR::isr169, 0x08, 0x8E);
    IDT::setGate(170, (uint32_t)ISR::isr170, 0x08, 0x8E);
    IDT::setGate(171, (uint32_t)ISR::isr171, 0x08, 0x8E);
    IDT::setGate(172, (uint32_t)ISR::isr172, 0x08, 0x8E);
    IDT::setGate(173, (uint32_t)ISR::isr173, 0x08, 0x8E);
    IDT::setGate(174, (uint32_t)ISR::isr174, 0x08, 0x8E);
    IDT::setGate(175, (uint32_t)ISR::isr175, 0x08, 0x8E);
    IDT::setGate(176, (uint32_t)ISR::isr176, 0x08, 0x8E);
    IDT::setGate(177, (uint32_t)ISR::isr177, 0x08, 0x8E);
    IDT::setGate(178, (uint32_t)ISR::isr178, 0x08, 0x8E);
    IDT::setGate(179, (uint32_t)ISR::isr179, 0x08, 0x8E);
    IDT::setGate(180, (uint32_t)ISR::isr180, 0x08, 0x8E);
    IDT::setGate(181, (uint32_t)ISR::isr181, 0x08, 0x8E);
    IDT::setGate(182, (uint32_t)ISR::isr182, 0x08, 0x8E);
    IDT::setGate(183, (uint32_t)ISR::isr183, 0x08, 0x8E);
    IDT::setGate(184, (uint32_t)ISR::isr184, 0x08, 0x8E);
    IDT::setGate(185, (uint32_t)ISR::isr185, 0x08, 0x8E);
    IDT::setGate(186, (uint32_t)ISR::isr186, 0x08, 0x8E);
    IDT::setGate(187, (uint32_t)ISR::isr187, 0x08, 0x8E);
    IDT::setGate(188, (uint32_t)ISR::isr188, 0x08, 0x8E);
    IDT::setGate(189, (uint32_t)ISR::isr189, 0x08, 0x8E);
    IDT::setGate(190, (uint32_t)ISR::isr190, 0x08, 0x8E);
    IDT::setGate(191, (uint32_t)ISR::isr191, 0x08, 0x8E);
    IDT::setGate(192, (uint32_t)ISR::isr192, 0x08, 0x8E);
    IDT::setGate(193, (uint32_t)ISR::isr193, 0x08, 0x8E);
    IDT::setGate(194, (uint32_t)ISR::isr194, 0x08, 0x8E);
    IDT::setGate(195, (uint32_t)ISR::isr195, 0x08, 0x8E);
    IDT::setGate(196, (uint32_t)ISR::isr196, 0x08, 0x8E);
    IDT::setGate(197, (uint32_t)ISR::isr197, 0x08, 0x8E);
    IDT::setGate(198, (uint32_t)ISR::isr198, 0x08, 0x8E);
    IDT::setGate(199, (uint32_t)ISR::isr199, 0x08, 0x8E);
    IDT::setGate(200, (uint32_t)ISR::isr200, 0x08, 0x8E);
    IDT::setGate(201, (uint32_t)ISR::isr201, 0x08, 0x8E);
    IDT::setGate(202, (uint32_t)ISR::isr202, 0x08, 0x8E);
    IDT::setGate(203, (uint32_t)ISR::isr203, 0x08, 0x8E);
    IDT::setGate(204, (uint32_t)ISR::isr204, 0x08, 0x8E);
    IDT::setGate(205, (uint32_t)ISR::isr205, 0x08, 0x8E);
    IDT::setGate(206, (uint32_t)ISR::isr206, 0x08, 0x8E);
    IDT::setGate(207, (uint32_t)ISR::isr207, 0x08, 0x8E);
    IDT::setGate(208, (uint32_t)ISR::isr208, 0x08, 0x8E);
    IDT::setGate(209, (uint32_t)ISR::isr209, 0x08, 0x8E);
    IDT::setGate(210, (uint32_t)ISR::isr210, 0x08, 0x8E);
    IDT::setGate(211, (uint32_t)ISR::isr211, 0x08, 0x8E);
    IDT::setGate(212, (uint32_t)ISR::isr212, 0x08, 0x8E);
    IDT::setGate(213, (uint32_t)ISR::isr213, 0x08, 0x8E);
    IDT::setGate(214, (uint32_t)ISR::isr214, 0x08, 0x8E);
    IDT::setGate(215, (uint32_t)ISR::isr215, 0x08, 0x8E);
    IDT::setGate(216, (uint32_t)ISR::isr216, 0x08, 0x8E);
    IDT::setGate(217, (uint32_t)ISR::isr217, 0x08, 0x8E);
    IDT::setGate(218, (uint32_t)ISR::isr218, 0x08, 0x8E);
    IDT::setGate(219, (uint32_t)ISR::isr219, 0x08, 0x8E);
    IDT::setGate(220, (uint32_t)ISR::isr220, 0x08, 0x8E);
    IDT::setGate(221, (uint32_t)ISR::isr221, 0x08, 0x8E);
    IDT::setGate(222, (uint32_t)ISR::isr222, 0x08, 0x8E);
    IDT::setGate(223, (uint32_t)ISR::isr223, 0x08, 0x8E);
    IDT::setGate(224, (uint32_t)ISR::isr224, 0x08, 0x8E);
    IDT::setGate(225, (uint32_t)ISR::isr225, 0x08, 0x8E);
    IDT::setGate(226, (uint32_t)ISR::isr226, 0x08, 0x8E);
    IDT::setGate(227, (uint32_t)ISR::isr227, 0x08, 0x8E);
    IDT::setGate(228, (uint32_t)ISR::isr228, 0x08, 0x8E);
    IDT::setGate(229, (uint32_t)ISR::isr229, 0x08, 0x8E);
    IDT::setGate(230, (uint32_t)ISR::isr230, 0x08, 0x8E);
    IDT::setGate(231, (uint32_t)ISR::isr231, 0x08, 0x8E);
    IDT::setGate(232, (uint32_t)ISR::isr232, 0x08, 0x8E);
    IDT::setGate(233, (uint32_t)ISR::isr233, 0x08, 0x8E);
    IDT::setGate(234, (uint32_t)ISR::isr234, 0x08, 0x8E);
    IDT::setGate(235, (uint32_t)ISR::isr235, 0x08, 0x8E);
    IDT::setGate(236, (uint32_t)ISR::isr236, 0x08, 0x8E);
    IDT::setGate(237, (uint32_t)ISR::isr237, 0x08, 0x8E);
    IDT::setGate(238, (uint32_t)ISR::isr238, 0x08, 0x8E);
    IDT::setGate(239, (uint32_t)ISR::isr239, 0x08, 0x8E);
    IDT::setGate(240, (uint32_t)ISR::isr240, 0x08, 0x8E);
    IDT::setGate(241, (uint32_t)ISR::isr241, 0x08, 0x8E);
    IDT::setGate(242, (uint32_t)ISR::isr242, 0x08, 0x8E);
    IDT::setGate(243, (uint32_t)ISR::isr243, 0x08, 0x8E);
    IDT::setGate(244, (uint32_t)ISR::isr244, 0x08, 0x8E);
    IDT::setGate(245, (uint32_t)ISR::isr245, 0x08, 0x8E);
    IDT::setGate(246, (uint32_t)ISR::isr246, 0x08, 0x8E);
    IDT::setGate(247, (uint32_t)ISR::isr247, 0x08, 0x8E);
    IDT::setGate(248, (uint32_t)ISR::isr248, 0x08, 0x8E);
    IDT::setGate(249, (uint32_t)ISR::isr249, 0x08, 0x8E);
    IDT::setGate(250, (uint32_t)ISR::isr250, 0x08, 0x8E);
    IDT::setGate(251, (uint32_t)ISR::isr251, 0x08, 0x8E);
    IDT::setGate(252, (uint32_t)ISR::isr252, 0x08, 0x8E);
    IDT::setGate(253, (uint32_t)ISR::isr253, 0x08, 0x8E);
    IDT::setGate(254, (uint32_t)ISR::isr254, 0x08, 0x8E);
    IDT::setGate(255, (uint32_t)ISR::isr255, 0x08, 0x8E);

    idt_flush((uint32_t)&idt_ptr);
}

// Set the value of one GDT entry
void GDT::setGate (int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

void IDT::setGate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;

    idt_entries[num].selector = sel;
    idt_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags = flags /* | 0x60 */;
}